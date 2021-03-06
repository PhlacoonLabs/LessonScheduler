#include "stdafx.h"

#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

enum {
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY,
	DONT_CARE
};

#define BLACK_LISTED_DAYS	0

struct Date { int iYear; int iMonth; int iDay; int iDayOfWeek; };

inline bool IsDayBlackListed(Date *dTestedDay, int iYear, int iMonth, int iDay) {
#if BLACK_LISTED_DAYS>0
	assert(dTestedDay != nullptr);
	return dTestedDay->iYear == iYear && dTestedDay->iMonth == iMonth && dTestedDay->iDay == iDay;
#else
	return false;
#endif
}

int main(int iArgC, char**lpszArgV) {

	int iMacroArguments = 2;
	int iLessonsPerArgument[2] = { 2, 7 }, iTotalLessons = 0;
	Date dArgumentStartTimes[2] = { {2018, 11, 2, FRIDAY}, {2018, 11, 20, TUESDAY} };
#if BLACK_LISTED_DAYS > 0
	Date dBlackListedDays[BLACK_LISTED_DAYS] = {
		{ 2018, 11, 21, DONT_CARE }
	};
	int iIthBlacklistedDay = 0;
#endif
	char const* szLessonArgument[9] = {
		"Lab introduction: overview of flex \\& bison. Introduction to lexing/lexers, parsing/parsers. Using Flex.",
		"Lexical Analysis: Flex's start condition, ambiguous specifications and exercises.",
		"Syntactic Analysis: introduction to bison, parsing and parsers.",
		"Syntactic Analysis: ",
		"Fri",
		"Sat",
		"Sun",
		"Sun",
		"Summary about interpretation and compilation."
	};

	int iYear = -1, iMonth = -1, iDay = -1;
	int iDayOfWeek = SUNDAY;

	bool bWeeklySchedule[7] =   { false,  true,  true,  true, false,  false,  false };
	char const* szDayNames[7] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
	int iDaysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	std::cout << "\\documentclass{report}\\usepackage[table]{xcolor}\\begin{document}\\title{FLC Lab Schedule}\\maketitle" << endl;
	for (int iArgument = 0; iArgument < iMacroArguments; iArgument++) {
		iYear = dArgumentStartTimes[iArgument].iYear;
		iMonth = dArgumentStartTimes[iArgument].iMonth;
		iDay = dArgumentStartTimes[iArgument].iDay;
		iDayOfWeek = dArgumentStartTimes[iArgument].iDayOfWeek;

		std::cout << "\\begin{center}\\begin{tabular}{|l|l|l|}" << endl;
		std::cout << "\t\\hline Day&\\#&Topic\\\\\\hline" << endl;
		for (int iIthLesson = 0; iIthLesson < iLessonsPerArgument[iArgument]; ) {
			if (bWeeklySchedule[iDayOfWeek]) {
				bool bIsDayBlackListed = false;
#if BLACK_LISTED_DAYS > 0
				bIsDayBlackListed = IsDayBlackListed(&dBlackListedDays[iIthBlacklistedDay], iYear, iMonth, iDay);
				iIthBlacklistedDay = bIsDayBlackListed && iIthBlacklistedDay < BLACK_LISTED_DAYS ? iIthBlacklistedDay + 1 : iIthBlacklistedDay;
#else
				bIsDayBlackListed = false;
#endif
				if (bIsDayBlackListed) {
					std::cout << "\t\\rowcolor{red}" << endl;
					std::cout << "\t" << szDayNames[iDayOfWeek] << " " << iYear << "\\textbackslash" << iMonth << "\\textbackslash" << iDay << "&-&CANCELLED\\\\\\hline" << endl;
			} else {
					std::cout << "\t\\rowcolor{green}" << endl;
					std::cout << "\t" << szDayNames[iDayOfWeek] << " " << iYear << "\\textbackslash" << iMonth << "\\textbackslash" << iDay << "&" << iTotalLessons + 1 << "&" << szLessonArgument[iTotalLessons] << "\\\\\\hline" << endl;
					iIthLesson++;
					iTotalLessons++;
				}
		} else {
				std::cout << "\t\\rowcolor{white}" << endl;
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
			} else {
				iDay += 1;
			}
			iDayOfWeek = (iDayOfWeek + 1) % 7;
	}
		std::cout << "\\end{tabular}\\end{center}" << endl;
}
	std::cout << "\\end{document}" << endl;
	return 0;
		}
