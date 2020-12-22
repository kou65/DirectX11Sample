
#ifndef CONVERT_H
#define CONVERT_H

#include<vector>
#include<string>
#include<iostream>





namespace Utility {


	// MEMO InputOutputに変える
	/**
	* @namespace Io Input/Outputまとめ
	*/
	namespace IOFunction{


		/**
		* @brief 文字分割
		*/
		std::vector<std::string> SplitStr(
			char cut_base_str,
			const std::string &string
		);


		/**
		* @brief 文字分割
		*/
		void SplitStr(
			char *m_root_path,
			const char*file_path,
			char split_str
		);


		/**
		* @brief 数字から文字列へ変換
		*/
		std::string ToString(int num);


		/**
		* @brief 文字列から数字へ変換
		*/
		int ToIntValue(const std::string &str);


		/**
		* @brief 文字列から数字へ変換
		*/
		int ToIntValue(const char*str);


		/**
		* @brief 文字列連結関数
		*/
		bool IsStrCmp(
			const char*str_cmp1,
			const char*str_cmp2
		);


		/**
		* @brief 文字列を読み込んでるかどうか
		*/
		bool IsStrInclude(
			const char*str1,
			const char*str2
		);


		/**
		* @brief リテラル文字からワイド文字へ変換(ナンバリングされている理由は処理が違う)
		*/
		bool ToWString1(
			const std::string& str,
			std::wstring& wstr
		);


		/**
		* @brief リテラル文字からワイド文字へ変換
		*/
		bool ToWString2(
			const std::string& str,
			std::wstring& wstr
		);
	}
}

#endif