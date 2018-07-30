#include "stdafx.h"

#include <iostream>
#include <cstdlib>

using namespace std;

enum {
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
};

struct Argument { int iYear; int iMonth; int iDay; int iDayOfWeek; };

int main(int iArgC, char**lpszArgV) {

	int iMacroArguments = 2;
	int iLessonsPerArgument[2] = {2, 7}, iTotalLessons = 0;
	Argument tArgumentStartTimes[2] = { {2018, 11, 2, FRIDAY}, {2018, 11, 20, MONDAY} };

	int iYear = -1, iMonth = -1, iDay = -1;
	int iDayOfWeek = SUNDAY;

	bool bWeeklySchedule[7] = { true, false, false, true, true, false, false };
	char const* szDayNames[7] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

	char const* szLessonArgument[9] = {
		"Lexical Analysis: introduction to flex, lexing and lexers.",
		"Lexical Analysis: more in depth lexing.",
		"Syntactic Analysis: introduction to bison, parsing and parsers.",
		"Thu",
		"Fri",
		"Sat",
		"Sun",
		"Sun",
		"Summary about interpretation and compilation."
	};


	int iDaysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	std::cout << "\\documentclass{report}\\usepackage[table]{xcolor}\\begin{document}\\title{FLC Lab Schedule}\\maketitle" << endl;
	for (int iArgument = 0; iArgument < iMacroArguments; iArgument++) {
		iYear = tArgumentStartTimes[iArgument].iYear;
		iMonth = tArgumentStartTimes[iArgument].iMonth;
		iDay = tArgumentStartTimes[iArgument].iDay;
		iDayOfWeek = tArgumentStartTimes[iArgument].iDayOfWeek;

		std::cout << "\\begin{center}\\begin{tabular}{|l|l|l|}" << endl;
		std::cout << "\t\\hline Day&\\#&Argument\\\\\\hline" << endl;
		for (int iIthLesson = 0; iIthLesson < iLessonsPerArgument[iArgument]; ) {
			if (bWeeklySchedule[iDayOfWeek]) {
				std::cout << "\t\\rowcolor{green}" << endl;
				std::cout << "\t" << szDayNames[iDayOfWeek] << " " << iYear << "\\textbackslash" << iMonth << "\\textbackslash" << iDay << "&" << iTotalLessons+1 << "&"<< szLessonArgument[iTotalLessons] <<"\\\\\\hline" << endl;
				iIthLesson++;
				iTotalLessons++;
			} else {
				std::cout << "\t\\rowcolor{gray}" << endl;
				std::cout << "\t" << szDayNames[iDayOfWeek] << " " << iYear << "\\textbackslash" << iMonth << "\\textbackslash" << iDay << "&-&-\\\\\\hline" << endl;
			}
			if (iDaysPerMonth[iMonth - 1] == iDay) {
				if (iMonth == 12) {
					iYear = iYear + 1; iMonth = 1;
					if (iYear % 4 == 0) { iDaysPerMonth[2 - 1] = 29; }
				} else {
					iMonth = iMonth + 1;
				}
				iDay = 1;
			}
			else {
				iDay += 1;
			}
			iDayOfWeek = (iDayOfWeek + 1) % 7;
		}
		std::cout << "\\end{tabular}\\end{center}" << endl;
	}
	std::cout << "\\end{document}" << endl;
	return 0;
}
