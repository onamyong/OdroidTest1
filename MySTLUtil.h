#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <random>

class MySTLUtil {
public:
	//
	// String Handlers
	//
	std::string rtrim(const std::string& s, const std::string t = " \t\n\r\f\v") {
		std::string str = s;
		str.erase(str.find_last_not_of(t) + 1);
		return str;
	}

	std::string ltrim(const std::string& s, const std::string t = " \t\n\r\f\v") {
		std::string str = s;
		str.erase(0, str.find_first_not_of(t));
		return str;
	}

	std::string trim(const std::string& s, const std::string t = " \t\n\r\f\v") {
		return ltrim(rtrim(s, t), t);
	}

	std::string elem(const std::string& s, const std::string t) {
		std::string str = s;
		size_t n;
		while ((n = str.find(t)) != std::string::npos) {
			str.erase(n, t.size());
		}
		return str;
	}

	template<typename... Args> std::string format(const std::string& fmt, Args... args) {
		int size = snprintf(nullptr, 0, fmt.c_str(), args...) + 1;
		if (size <= 0) throw std::runtime_error("Error during formatting");
		std::unique_ptr<char> buf(new char[size]);
		snprintf(buf.get(), size, fmt.c_str(), args...);
		return std::string(buf.get());
	}

	std::vector<std::string> readLine(const std::string& line, const std::string t = " ") {
		std::string s = trim(line);
		std::vector<std::string> rsv;

		while (s != "") {
			size_t n = s.find_first_of(t);
			if (n == std::string::npos) {
				rsv.push_back(s);
				break;
			}
			else {
				rsv.push_back(s.substr(0, n));
				s.erase(0, s.find_first_of(t));
				s.erase(0, s.find_first_not_of(t));
			}
		}
		return rsv;
	}

	//
	// File Handlers
	//
	std::string readTextFile(const std::string pathname) {
		std::ifstream ifile(pathname);
		if (ifile.is_open()) {
			std::string text = "";
			while (!ifile.eof()) {
				std::string str;
				std::getline(ifile, str);
				text += str + "\r\n";
			}
			ifile.close();
			return text;
		}
		return "";
	}

	std::vector<std::string> readLines(const std::string lines) {
		std::vector<std::string> ret;
		std::stringstream textstream(lines);
		std::string line;
		while (std::getline(textstream, line)) {
			if (trim(line) == "") continue;
			ret.push_back(line);
		}
		return ret;
	}

	std::vector<std::string> readTextFileLines(const std::string pathname) {
		return readLines(readTextFile(pathname));
	}

	std::vector<std::filesystem::path> getPathList(const std::string pathname) {
		std::vector<std::filesystem::path> pathlist;
		for (const auto& file : std::filesystem::directory_iterator(pathname)) {
			pathlist.push_back(file.path());
		}
		return pathlist;
	}

	std::string findFile(const std::string pathname, const std::string filename) {
		for (const auto& file : std::filesystem::directory_iterator(pathname)) {
			if (file.is_directory()) continue;
			if (file.path().filename().string() == filename) return file.path().string();
		}
		return "";
	}
};
