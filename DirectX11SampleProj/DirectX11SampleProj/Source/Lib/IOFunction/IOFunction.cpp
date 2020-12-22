#include"IOFunction.h"
#include <locale>
#include<stdlib.h>



namespace Utility {


	namespace IOFunction {

		std::vector<std::string> SplitStr(
			char cut_base_str,
			const std::string &string
		) {

			std::string string_buffer;
			const char*string_ = string.c_str();

			std::vector<std::string> out_string_list;


			// 文字列が存在しないなら
			if (string.c_str() == NULL) {
				return out_string_list;
			}

			for (unsigned int i = 0; i < strlen(string.c_str()); i++) {

				// 文字列加算
				string_buffer += string_[i];

				// 区切りを指定
				if (cut_base_str == string_[i]) {

					std::string str(string_buffer);

					// 文字列配列に追加
					out_string_list.push_back(str);

					string_buffer.clear();
				}
			}

			// 最後の文字列算出
			{

				std::string str(string_buffer);

				out_string_list.push_back(str);
			}

			return out_string_list;
		}


		void SplitStr(
			char *m_root_path,
			const char*file_path,
			char split_str = '/'
		) {

			int str_num = (int)strlen(file_path);
			str_num *= 2;

			strcpy_s(
				m_root_path,
				str_num,
				file_path
			);

			size_t i;
			for (i = strlen(m_root_path); 0 < i; i--)
			{
				if (m_root_path[i] == split_str) break;
			}
			m_root_path[i] = '\0';

		}

		bool IsStrCmp(
			const char*str_cmp1,
			const char*str_cmp2
		) {

			int result = strcmp(str_cmp1, str_cmp2);

			// 0なら文字列が一致
			if (result == 0) {
				return true;
			}
			else {
				return false;
			}
		}

		bool IsStrInclude(
			const char*str1,
			const char*str2
		) {

			if (strstr(str1, str2) == NULL) {
				return false;
			}

			return true;
		}


		std::string ToString(int num) {
			return std::to_string(num);
		}

		int ToIntValue(const std::string &str) {
			return atoi(str.c_str());
		}

		int ToIntValue(const char*str) {
			return atoi(str);
		}


		// 日本語を使うには
		// setlocale( LC_ALL, "Japanese" );

		bool ToWString1(const std::string& str, std::wstring& wstr)
		{
			size_t size;
			if (0 != mbstowcs_s(&size, NULL, 0, str.c_str(), 0)) {
				return false;
			}
			std::vector<wchar_t> wch(size);
			if (0 != mbstowcs_s(&size, wch.data(), wch.size(), str.c_str(), str.length())) {
				return false;
			}
			wstr = wch.data();
			return true;
		}


		bool ToWString2(const std::string& str, std::wstring& wstr)
		{
			std::locale loc("Japanese");//日本語

			// code_conv char->wchar_tの変換クラス
			typedef std::codecvt<wchar_t, char, std::mbstate_t> code_conv;

			// 変換するファセットがあるか
			if (!std::has_facet<code_conv>(loc)) { return false; }

			// 日本語でのchar->wchar_t変換クラスのインスタンス取得
			// ライブラリが用意しているインスタンス（ファセット）を使う
			const code_conv& conv = std::use_facet<code_conv>(loc);

			//変換後のサイズ
			const size_t str_size = str.length() + 1;//char文字列長さ(\0含む)
			std::mbstate_t state_len = { 0 };
			const char* ch = str.c_str();
			size_t size = conv.length(state_len, ch, ch + str_size, str_size);

			// 変換
			std::vector<wchar_t> wch(str_size);
			const char* ch_next = 0;
			wchar_t* wch_next = 0;
			std::mbstate_t state = { 0 };
			if (std::codecvt_base::ok
				!= conv.in(state, ch, ch + str.size(), ch_next,
					wch.data(), wch.data() + wch.size(), wch_next))
			{
				return false;
			}

			wstr = wch.data();
			return true;
		}
	}
}