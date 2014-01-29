﻿//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ElementReferenceArrayChainTickers.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ElementReferenceArrayChainTickers.h"
#include "ReferenceDataRequest/ElementReferenceArrayChainTickersItem.h"
#include <vector>
#include "Types/RandomDataGenerator.h"
#include "Types/DisplayFormats.h"
#include "BloombergTypes/Datetime.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ElementReferenceArrayChainTickers::ElementReferenceArrayChainTickers(const std::string& underlier, unsigned numPoints, const std::string& strDtExp, OptionalityEnum::EnumType optionality) :
			ElementReferenceArray("CHAIN_TICKERS", std::vector<ElementPtr*>())
		{
			int indexSpace = underlier.find(' ');
			std::string ticker = underlier.substr(0, indexSpace); //assume that the underlier takes the form "ABC US EQUITY"

			Datetime dtExp;
			if(strDtExp.length() < 4)
			{
				dtExp = Datetime::Today();
				dtExp.addMonths(1);
				dtExp.addDays(-((long)dtExp.day()));
				dtExp.addDays(20); //assume the 20th of the month
			}
			else if(strDtExp.length() == 8)
			{
				if(!DisplayFormats::HistoricalOrReferenceRequests_TryParseInput(strDtExp, dtExp))
					throw elementPtrEx;
			}
			else if(strDtExp.length() == 6)
			{
				stringstream ssDtExp;
				ssDtExp << strDtExp << "20";

				if(!DisplayFormats::HistoricalOrReferenceRequests_TryParseInput(ssDtExp.str(), dtExp))
					throw elementPtrEx;
			}
			else if (strDtExp[strDtExp.length() - 1] == 'F')
			{
				std::string strNumMonths = strDtExp.substr(0, strDtExp.length() - 1);
				int numMonths = atoi(strNumMonths.c_str());

				dtExp = Datetime::Today();
				dtExp.addMonths(numMonths);
				dtExp.addDays(-((long)dtExp.day()));
				dtExp.addDays(20); //assume the 20th of the month
			}
			else
				throw elementPtrEx;

			int strike = RandomDataGenerator::Strike();
			for (unsigned count = 0; count < numPoints; count++, strike += 5)
			{
				ElementPtr * elm = new ElementReferenceArrayChainTickersItem(ticker, dtExp, optionality, strike);
				this->_values.push_back(elm);
			}

		}

	}
}