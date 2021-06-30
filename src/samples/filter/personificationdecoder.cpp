/** Copyright 2021 Tiny Oh, Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "personificationdecoder.h"
#define ELPP_THREAD_SAFE
#include "easylogging++.h"

#include "async++.h"
//INITIALIZE_EASYLOGGINGPP


PersonificationDecoder::PersonificationDecoder():
  code_step1_trust_count(0),
  m_code_step1_tmp_start_tag(false),
  m_decode_step2_tmp_start_tag(false),
  m_samplingRate(20),
  _samplingIndex(0) {}

PersonificationDecoder::~PersonificationDecoder()
{}

configuru::Config PersonificationDecoder::defaultParams() {
  LOG(INFO) << __FUNCTION__ << __LINE__;
  return {};
}

bool PersonificationDecoder::reset() {
  _samplingIndex = 0;
  m_code_step1_tmp.clear();
  m_code_step1_tmp_start_tag = false;
  m_decode_step2_tmp_start_tag = false;
  return true;
}

PersonificationDecoder::S_RES PersonificationDecoder::ThreadProcess(
    const std::string &tp,
    const int &sz, const bool &tg, const float &avg,
    const float &scale, std::shared_ptr<std::vector<float>> data) {
  auto cache = *data;
  auto avg_fix = avg * scale;
  bool status_change_tag = (*data)[0] > avg_fix;
  S_RES res = {std::make_shared<std::vector<float>>(cache), "", 0};
  std::string tms = "";
  std::vector<int> tm;
  for(int i = 0; i < sz; i++) {
    static int count_i = 0;
    if ((*data)[static_cast<size_t>(i)] > avg_fix) {
      cache[static_cast<size_t>(i)] = 1.f;
      if (tg && !status_change_tag) {
        int res_local = 4;
        if (count_i > 150) {
          res_local = 6;
        } else if (count_i > 15) {
          res_local = 5;
        }

        if (res_local == 4) {
            res.confidence_level = 12;
            return res;
        }
        if (i > 30 && i < (sz - 30)) {
          tm.push_back(res_local);
        }
        count_i = 0;
        status_change_tag = true;
      }
    } else {
      cache[static_cast<size_t>(i)] = 0.f;
      if (tg && status_change_tag) {
        int res_local = 1;
        if (count_i > 130) {
          res_local = 3;
        } else if (count_i > 15) {
          res_local = 2;
        }
        if (res_local == 1) {
            res.confidence_level = 12;
            return res;
        }
        if (i > 30 && i < (sz - 30)) {
          tm.push_back(res_local);
        }
        count_i = 0;
        status_change_tag = false;
      }
    }
    count_i++;
  }
  if (tm.size() > 3) {
    for (size_t h = tm.size() - 2; h > 0; h--) {
      tms += std::to_string(tm[h]);
    }
    _log_locker.lock();
    std::cout  << scale << " target: " << tms << std::endl;
    std::cout.flush();
    _log_locker.unlock();
    static int e_count = 0;

    // start to decode.
    for (size_t h = tm.size() - 2; h > 0; h--) {
      tms += std::to_string(tm[h]);
    }

//    std::string tp;
//    for (size_t bp = m_code_step1_tmp_cur_head; bp < m_code_step1_tmp.size(); bp++) {
//      tp += m_code_step1_tmp[bp];
//    }
    auto asize = int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head);

//        std::cout  << scale <<" " << tp <<" " << tms << std::endl;

    // case 1:
    // xxxxx^abcdefg... + abcyyyyy -> xxxxx^abcyyyyy
    if (asize > 2 && !strncmp(tp.c_str(), tms.c_str(), 3))
        res.confidence_level = 1;
    // case 2:
    // xxxxx^abcdefg... + bcdyyyy -> xxxxxa^bcdyyyy
    else if (asize > 3 && !strncmp(tp.c_str() + 1, tms.c_str(), 3))
        res.confidence_level = 2;
    // case 3:
    // xxxxx^abc + bc -> xxxxxa^bc
    else if (asize == 3 && !strncmp(tp.c_str() + 1, tms.c_str(), 2))
        res.confidence_level = 3;
    // case 4:
    // xxxxx^ab + abcXXX -> xxxxx^abcXXX
    else if (asize == 2 && !strncmp(tp.c_str(), tms.c_str(), 2))
        res.confidence_level = 4;
    // case 5:
    // xxxxx^abcdxxxx + iabcdyyy -> xxxxx^abcdyyy
    else if (asize > 3 && tms.size() > 4 &&
             !strncmp(tp.c_str(), tms.c_str() + 1, 4))
        res.confidence_level = 5;
    // case 6:
    // xxxxx^abcdxxxx + iabcdyyy -> xxxxx^abcdyyy
    else if (asize > 3 && tms.size() > 5 &&
             !strncmp(tp.c_str(), tms.c_str() + 2, 4))
        res.confidence_level =6;
    // case 7:
    // xxxxx^jabcdexxx + iabcdyyyy -> xxxxxj^abcdyyy
    else if (asize > 4 &&tms.size() > 4 &&
             !strncmp(tp.c_str() + 1, tms.c_str() + 1, 4))
        res.confidence_level = 7;
    // case 8:
    // xxxxx^jabcdexxx + inabcdyyyy -> xxxxxj^abcdyyy
    else if (asize > 4 && tms.size() > 5 &&
             !strncmp(tp.c_str() + 1, tms.c_str() + 2, 4))
        res.confidence_level = 8;
    // case 9:
    // xxxxx^jkabcdxxxx + inabcdyyy -> xxxxxjk^abcdyyy
    else if (asize > 5 && tms.size() > 5 &&
             !strncmp(tp.c_str() + 2, tms.c_str() + 2, 4))
        res.confidence_level = 9;
    // case 10:
    // xxxxx^jkabcdxxxx + iabcdyyy -> xxxxxjk^abcdyyy
    else if (asize > 5 && tms.size() > 4 &&
             !strncmp(tp.c_str() + 2, tms.c_str() + 1, 4))
        res.confidence_level = 10;
    else {
      res.confidence_level = 11;
      if (tms.size() < 3) {
          return res;
      }
      std::string tp1;
      for (size_t bp = 0; bp < m_code_step1_tmp.size(); bp++) {
        tp1 += m_code_step1_tmp[bp];
      }
//          LOG(INFO) << "current cache: " << tp1 << "|| tm: " << tp <<" || curdecode_target: " << res.decode_res << " || head:" << m_code_step1_tmp_cur_head;
      e_count++;
      if (e_count > 2) {
        res.confidence_level = 12;
//            reset();
      }
    }

    if (res.confidence_level != 11 && res.confidence_level != 12) {
      e_count = 0;
    }
//        _log_locker.lock();
//        std::cout  << scale << "-------------"<< res.confidence_level << std::endl;
//        std::cout.flush();
//        _log_locker.unlock();
  }
  res.decode_res = tms;

  return res;
}

bool PersonificationDecoder::decodeBeforeWait(std::shared_ptr<std::vector<float>> data) {
  auto cache = *data;
  float average = 0.f;
  auto sz = static_cast<int>(data->size());
  for(int i = 0; i < sz; i++) {
    average += (*data)[static_cast<size_t>(i)] / sz;
  }

  bool tg = ++_samplingIndex >= m_samplingRate;
  if (tg) _samplingIndex = 0;

  std::string tp = "";
  if (tg && m_code_step1_tmp_start_tag) {
    for (size_t bp = m_code_step1_tmp_cur_head; bp < m_code_step1_tmp.size(); bp++) {
      tp += m_code_step1_tmp[bp];
    }
    LOG(INFO) << "tp: " << tp;

    float t1 = 0.997f;
    float t2 = 1.f;
    float t3 = 1.003f;

    auto task1 = async::spawn([&, this, data]() -> S_RES {
        return ThreadProcess(tp ,sz, tg, average, t1, data);
    });

    auto task2 = async::spawn([&, this, data]() -> S_RES {
        return ThreadProcess(tp ,sz, tg, average, t2, data);
    });

    auto task3 = async::spawn([&, this, data]() -> S_RES {
        return ThreadProcess(tp ,sz, tg, average, t3, data);
    });

    auto tasks_ = async::when_all(task1, task2, task3);

    auto task_check_ = tasks_.then([this, tg, sz](std::tuple< async::task<S_RES>,
                                                              async::task<S_RES>,
                                                              async::task<S_RES>> results) -> S_RES {

        if (m_code_step1_tmp_start_tag && tg) {
          std::cout<< std::get<0>(results).get().confidence_level
                   << " || "
                   << std::get<1>(results).get().confidence_level
                   << " || "
                   << std::get<2>(results).get().confidence_level
                   << " || "
                   << std::endl;
          std::cout.flush();
        }
        return {};
    });

    task_check_.get();
  }

  bool status_change_tag = (*data)[0] > average;

  std::vector<int> tm;
  for(int i = 0; i < sz; i++) {
    static int count_i = 0;
    if ((*data)[static_cast<size_t>(i)] > average) {
      cache[static_cast<size_t>(i)] = 1.f;
      if (tg && !status_change_tag) {
        int res = 4;
        if (count_i > 150) {
          res = 6;
        } else if (count_i > 15) {
          res = 5;
        }

        if (res == 4) {
          return false;
        }
        if (i > 30 && i < (sz - 30)) {
          tm.push_back(res);
        }
//          LOG(INFO) << "compute decode test 0:" << res <<"   "<< count_i;

        count_i = 0;
        status_change_tag = true;
      }
    } else {
      cache[static_cast<size_t>(i)] = 0.f;
      if (tg && status_change_tag) {
        int res = 1;
        if (count_i > 130) {
          res = 3;
        } else if (count_i > 15) {
          res = 2;
        }
        if (res == 1) {
          return false;
        }
//          LOG(INFO) << "compute decode test 1:" << res <<"   "<< count_i;
        if (i > 30 && i < (sz - 30)) {
          tm.push_back(res);
        }
        count_i = 0;
        status_change_tag = false;
      }
    }
    count_i++;
  }


  if (tg && tm.size() > 3) {
    if (!m_code_step1_tmp_start_tag ) {
      // before start
      std::string tms="";
      for (size_t h = tm.size() - 2; h > 0; h--) {
        tms += std::to_string(tm[h]);
      }
      if (m_code_step1_tmp_str == tms) {
        code_step1_trust_count ++;
        if (code_step1_trust_count > 2) {
          LOG(INFO) << "Repeat code repeat times > 2, start decode: ";
          m_code_step1_tmp_start_tag = true;
          for (size_t n = 0; n < tms.size(); n++) {
            m_code_step1_tmp.push_back(tms.c_str()[n]);
          }
          m_code_step1_tmp_cur_head = 0;
          m_decode_step2_tmp_cur_head = 0;
          code_step1_trust_count = 0;
        }
      } else {
        code_step1_trust_count = 0;
      }
      m_code_step1_tmp_str = tms;
//      LOG(INFO) << tms << ".";
    } else {
      // start to decode.
      std::string tms="";
      for (size_t h = tm.size() - 2; h > 0; h--) {
        tms += std::to_string(tm[h]);
      }

      std::string tp;
      for (size_t bp = m_code_step1_tmp_cur_head; bp < m_code_step1_tmp.size(); bp++) {
        tp += m_code_step1_tmp[bp];
      }
      int case_ = 0;
      static int e_count = 0;

      // case 1:
      // xxxxx^abcdefg... + abcyyyyy -> xxxxx^abcyyyyy
      if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) > 2 &&!strncmp(tp.c_str(), tms.c_str(), 3)) {
//            LOG(INFO) << "case 1";
        case_ = 1;
        if (tms.size() > tp.size()) {
//              LOG(INFO) << "tms.size()" << tms.size() << "|" << tp.size();
          for (size_t i = 0; i < tms.size() - tp.size(); i++) {
            m_code_step1_tmp.push_back('0');
          }
        }
        for (size_t n = 0; n < tms.size(); n++) {
          m_code_step1_tmp[m_code_step1_tmp_cur_head + n] = tms.c_str()[n];
        }
      }
      // case 2:
      // xxxxx^abcdefg... + bcdyyyy -> xxxxxa^bcdyyyy
      else if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) > 3 &&
          !strncmp(tp.c_str() + 1, tms.c_str(), 3)) {
//            LOG(INFO) << "case 2";
        case_ = 2;
        if (tms.size() > (tp.size() - 1)) {
//              LOG(INFO) << "tms.size()" << tms.size() << "|" << tp.size() - 1;
          for (size_t i = 0; i < (tms.size() - (tp.size() - 1)); i++) {
            m_code_step1_tmp.push_back('0');
          }
        }
        for (size_t n = 0; n < tms.size(); n++) {
          m_code_step1_tmp[m_code_step1_tmp_cur_head + 1 + n] = tms.c_str()[n];
        }
        m_code_step1_tmp_cur_head++;
      }

      // case 3:
      // xxxxx^abc + bc
      else if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) == 3 &&
          !strncmp(tp.c_str() + 1, tms.c_str(), 2)) {
//        LOG(INFO) << "case 3" << "[warning] may error occor.";
        case_ = 3;
        m_code_step1_tmp_cur_head++;
      }

      // case 4:
      // xxxxx^ab + abcXXX
      else if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) == 2 &&
               !strncmp(tp.c_str(), tms.c_str(), 2)) {
        case_ = 4;
        if (tms.size() > (tp.size())) {
//          LOG(INFO) << "tms.size()" << tms.size() << "|" << tp.size();
          for (size_t i = 0; i < (tms.size() - (tp.size())); i++) {
            m_code_step1_tmp.push_back('0');
          }
        }
        for (size_t n = 0; n < tms.size(); n++) {
          m_code_step1_tmp[m_code_step1_tmp_cur_head + n] = tms.c_str()[n];
        }
      // case 5:
      // xxxxx^abcdxxxx + iabcdyyy -> xxxxx^abcdyyy
      } else if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) > 3 &&
                 tms.size() > 4 &&
                 !strncmp(tp.c_str(), tms.c_str() + 1, 4)) {
        case_ = 5;
        if ((tms.size() - 1) > (tp.size())) {
        //          LOG(INFO) << "tms.size()" << tms.size() << "|" << tp.size();
        for (size_t i = 0; i < ((tms.size() - 1) - (tp.size())); i++) {
          m_code_step1_tmp.push_back('0');
        }
        }
        for (size_t n = 1; n < tms.size(); n++) {
          m_code_step1_tmp[m_code_step1_tmp_cur_head + n - 1] = tms.c_str()[n];
        }
      // case 6:
      // xxxxx^abcdxxxx + iabcdyyy -> xxxxx^abcdyyy
      } else if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) > 3 &&
                 tms.size() > 5 &&
                 !strncmp(tp.c_str(), tms.c_str() + 2, 4)) {
        case_ =6;
        if ((tms.size() - 2) > (tp.size())) {
          //          LOG(INFO) << "tms.size()" << tms.size() << "|" << tp.size();
          for (size_t i = 0; i < ((tms.size() - 2) - (tp.size())); i++) {
            m_code_step1_tmp.push_back('0');
          }
        }
        for (size_t n = 2; n < tms.size(); n++) {
          m_code_step1_tmp[m_code_step1_tmp_cur_head + n - 2] = tms.c_str()[n];
        }
      // case 7:
      // xxxxx^jabcdexxx + iabcdyyyy -> xxxxxj^abcdyyy
      } else if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) > 4 &&
                 tms.size() > 4 &&
                 !strncmp(tp.c_str() + 1, tms.c_str() + 1, 4)) {
        LOG(INFO) << "case 7";
        case_ = 7;
        if ((tms.size() - 1) > (tp.size() - 1)) {
        //          LOG(INFO) << "tms.size()" << tms.size() << "|" << tp.size();
          for (size_t i = 0; i < ((tms.size() - 1) - (tp.size() - 1)); i++) {
            m_code_step1_tmp.push_back('0');
          }
        }
        for (size_t n = 1; n < tms.size(); n++) {
          m_code_step1_tmp[m_code_step1_tmp_cur_head + n] = tms.c_str()[n];
        }
        m_code_step1_tmp_cur_head++;
      // case 8:
      // xxxxx^jabcdexxx + inabcdyyyy -> xxxxxj^abcdyyy
      } else if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) > 4 &&
                 tms.size() > 5 &&
                 !strncmp(tp.c_str() + 1, tms.c_str() + 2, 4)) {
        LOG(INFO) << "case 8";
        case_ = 8;
        if ((tms.size() - 2) > (tp.size() - 1)) {
        //          LOG(INFO) << "tms.size()" << tms.size() << "|" << tp.size();
         for (size_t i = 0; i < ((tms.size() - 2) - (tp.size() - 1)); i++) {
           m_code_step1_tmp.push_back('0');
         }
        }
        for (size_t n = 2; n < tms.size(); n++) {
          m_code_step1_tmp[m_code_step1_tmp_cur_head + n - 1] = tms.c_str()[n];
        }
        m_code_step1_tmp_cur_head++;
      // case 9:
      // xxxxx^jkabcdxxxx + inabcdyyy -> xxxxxjk^abcdyyy
      } else if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) > 5 &&
                tms.size() > 5 &&
                !strncmp(tp.c_str() + 2, tms.c_str() + 2, 4)) {
        LOG(INFO) << "case 9";
        case_ = 9;
        if ((tms.size() - 2) > (tp.size() - 2)) {
          //          LOG(INFO) << "tms.size()" << tms.size() << "|" << tp.size();
          for (size_t i = 0; i < ((tms.size() - 2) - (tp.size() - 2)); i++) {
            m_code_step1_tmp.push_back('0');
          }
        }
        for (size_t n = 2; n < tms.size(); n++) {
          m_code_step1_tmp[m_code_step1_tmp_cur_head + n] = tms.c_str()[n];
        }
        m_code_step1_tmp_cur_head += 2;
      // case 10:
      // xxxxx^jkabcdxxxx + iabcdyyy -> xxxxxjk^abcdyyy
      } else if (int(m_code_step1_tmp.size()) - int(m_code_step1_tmp_cur_head) > 5 &&
                 tms.size() > 4 &&
                 !strncmp(tp.c_str() + 2, tms.c_str() + 1, 4)) {
        LOG(INFO) << "case 10";
        case_ = 10;
        if ((tms.size() - 1) > (tp.size() - 2)) {
        //          LOG(INFO) << "tms.size()" << tms.size() << "|" << tp.size();
        for (size_t i = 0; i < ((tms.size() - 1) - (tp.size() - 2)); i++) {
         m_code_step1_tmp.push_back('0');
        }
        }
        for (size_t n = 2; n < tms.size(); n++) {
        m_code_step1_tmp[m_code_step1_tmp_cur_head + n] = tms.c_str()[n - 1];
        }
        m_code_step1_tmp_cur_head += 2;
      } else {
        if (tms.size() < 3) {
          return false;
        }
        LOG(INFO) << "other case";
        std::string tp1;
        for (size_t bp = 0; bp < m_code_step1_tmp.size(); bp++) {
          tp1 += m_code_step1_tmp[bp];
        }

        LOG(INFO) << "current cache: " << tp1 << "|| tm: " << tp <<" || curdecode_target: " << tms << " || head:" << m_code_step1_tmp_cur_head;
        e_count++;
        if (e_count > 2) {
          reset();
        }
      }

      if (case_ != 0) {
        e_count = 0;
      }

#define DEBUG_CAT_STR
#ifdef DEBUG_CAT_STR
      LOG(INFO) << "case: " << case_ << "  curdecode_target: " << tms << " head: " << tp;
#endif

      if (case_ == 2 ||
          case_ == 3 ||
          case_ == 5 ||
          case_ == 7 ||
          case_ == 6 ||
          case_ == 8) {
        if (!m_decode_step2_tmp_start_tag &&
            (m_code_step1_tmp[m_code_step1_tmp_cur_head] == '3' ||
            m_code_step1_tmp[m_code_step1_tmp_cur_head] == '6')) {
          m_decode_step2_tmp_cur_head = m_code_step1_tmp_cur_head;
          m_decode_step2_tmp_start_tag = TRUE;
        }
        if (m_decode_step2_tmp_start_tag) {
          while (m_code_step1_tmp_cur_head > m_decode_step2_tmp_cur_head) {
            int t1 = m_code_step1_tmp[m_decode_step2_tmp_cur_head + 1];
            int t2 = m_code_step1_tmp[m_decode_step2_tmp_cur_head];
//            LOG(INFO) << m_code_step1_tmp_cur_head
//                      << "||" << m_decode_step2_tmp_cur_head << "|||" << t1 << "|||" << t2;

            if (t2 == '3') {
              if (t1 == '6') {
//                LOG(INFO) << "file_location" << "---------------------" << 1;
                _resualt->push_back('1');
                m_decode_step2_tmp_cur_head++;
              } else if (t1 == '5') {
//                LOG(INFO) << "file_location" << "---------------------" << 1;
                _resualt->push_back('1');
                m_decode_step2_tmp_cur_head++;
              }
            } else if (t2 == '6') {
              if (t1 == '3') {
//                LOG(INFO) << "file_location" << "---------------------" << 0;
                _resualt->push_back('0');
                m_decode_step2_tmp_cur_head++;
              } else if (t1 == '2') {
//                LOG(INFO) << "file_location" << "---------------------" << 0;
                _resualt->push_back('0');
                m_decode_step2_tmp_cur_head++;
              }
            } else if (t2 == '2') {
              if (t1 == '6') {
//                LOG(INFO) << "file_location" << "Clock error!";
                _resualt->push_back('X');
                m_decode_step2_tmp_cur_head++;
              } else if (t1 == '5') {
//                LOG(INFO) << "file_location" << "---------------------" << 0;
                _resualt->push_back('0');
                m_decode_step2_tmp_cur_head++;
                m_decode_step2_tmp_cur_head++;
              }
            } else if (t2 == '5') {
              if (t1 == '3') {
//                LOG(INFO) << "file_location" << "Clock error!";
                _resualt->push_back('X');
                m_decode_step2_tmp_cur_head++;
              } else if (t1 == '2') {
//                LOG(INFO) << "file_location" << "---------------------" << 1;
                _resualt->push_back('1');
                m_decode_step2_tmp_cur_head++;
                m_decode_step2_tmp_cur_head++;
              }
            }

            if (t1 == '0' || t2 == '0') {
              LOG(INFO) << "error";
              reset();
            }
          }
        }
      }
    }
  }
  _displayBuffer = std::make_shared<std::vector<float>>(cache);

  return true;
}
bool PersonificationDecoder::decodeAfterWait() {
//  LOG(INFO) << __FUNCTION__ << __LINE__;
  return false;
}

