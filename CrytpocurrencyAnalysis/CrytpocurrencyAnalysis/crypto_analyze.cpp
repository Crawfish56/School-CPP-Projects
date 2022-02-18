/********************************************************************
Course: CSCI240.01
Professor: Dr. Ringenberg
Program Title: Cryptocurrency Data Analysis

//This program was initally used to sort out different crypto curerncies and then display their number of records, minimum price, maximum price,and average price.
// now this program uses stucts to increase readability. The structs are used to go through the file, input the correct values form the csv files and then a function is used
// to find the number of records, minimum price, maximum price,and average prices of the different coins. 
*********************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
using namespace std;

struct CryptoRecord {
	string coinNames;
	string coinSymbols;
	string recordDates;
	double marketCaps;
	double coinPrices;
};

struct CryptoStatData {
	string  cryptoName;
	double  totalPrice;
	int     totalRecords;
	double  minPrice;
	double  maxPrice;
};

struct HighPrices {
	static const int NUM_PRICES = 10;
	string name[NUM_PRICES];
	string date[NUM_PRICES];
	double price[NUM_PRICES];
};

void calcTopPrices(HighPrices& HighBTCPrices, CryptoRecord cryptos[], int NumCryptos);

void sortTopPrices(HighPrices& topPrices);
void writeTopPrices(ofstream& outFile, HighPrices& topPrices);

void computeCryptoStats(CryptoStatData CryptoStats[], int& numCryptos, CryptoRecord Cryptos[], int numCoins);

void writeCryptoStats(ofstream& outFile, CryptoStatData CryptoStats[], int numCryptos);

void readCryptoData(ifstream& inFile, CryptoRecord cryptos[], int& numCoins, int max);

void writeCryptoData(ofstream& outFile, CryptoRecord[], int numInputs);

string getSubstrUpToNextComma(string str, int& startPos);

void printCoinRecords(ofstream& outFile, CryptoRecord[], int numInputs);

void printMinMaxAvgPriceForEachCoin(ofstream& outFile, CryptoRecord[], int numInputs);

void printMinMaxAvgForCoin(ofstream& outFile, string curCoinName, int countOfCurrentCoin,
	double avgPrice, double minPrice, double maxPrice);
double min(double a, double b);

double max(double a, double b);

void printNumDaysMarketCapIncreasedForEachCoin(
	ofstream& outFile, CryptoRecord[], int numInputs);

void printHighestPriceIncreaseForEachCoin(
	ofstream& outFile, CryptoRecord[], int numInputs);

void printHighestPriceIncreaseForCoin(ofstream& outFile, string coinName, double val, double pct,
	string dateFrom, string dateTo);

void printHighestPricesForCoin(ofstream& outFile, string coinToAnalyze, CryptoRecord[], int numInputs);

void setprecisionBasedOnPrice(ofstream& outFile, double price);

int main() {

	//Initialize Variables.
	const int MAX_COINS = 5000;
	CryptoRecord Cryptos[MAX_COINS];

	const int MAX_STATS = 25;
	CryptoStatData CryptoStats[MAX_STATS];

	HighPrices HighBTCPrices;
	for (int i = 0; i < HighBTCPrices.NUM_PRICES; i++) {
		HighBTCPrices.price[i] = 0;
	}


	for (int i = 0; i < MAX_STATS; i++) {
		//initialize EVERY member element in the array   
		CryptoStats[i].cryptoName = "";
		CryptoStats[i].totalPrice = 0;
		CryptoStats[i].totalRecords = 0;
		CryptoStats[i].minPrice = numeric_limits<double>::max();
		CryptoStats[i].maxPrice = 0;
	}

	int		arrayNum = 0;
	int     numCoins = 0;
	int     numCryptos = 0;

	

	string    TempString;
	string    fileLine;

	string    in_filename = "coin_data_2018.csv";
	ifstream  inFile(in_filename);

	if (!inFile) {
		cout << "Error opening " << in_filename << " for reading. Exiting..." << endl;
		return 1;
	}

	readCryptoData(inFile, Cryptos, numCoins, MAX_COINS);
	inFile.close();


	string   out_filename = "coin_analysis2018.txt";
	ofstream outFile(out_filename);

	if (!outFile) {
		cout << "Error opening " << out_filename << " for writing. Exiting..." << endl;
		return 1;
	}

	computeCryptoStats(CryptoStats, numCryptos, Cryptos, numCoins);
	writeCryptoStats(outFile, CryptoStats, numCryptos);

	writeCryptoData(outFile, Cryptos, numCoins);
	calcTopPrices(HighBTCPrices, Cryptos, numCoins);
	writeTopPrices(outFile, HighBTCPrices);


	system("pause");
	return 0;

}
void writeTopPrices(ofstream& outFile, HighPrices& topPrices) {
	for (int i = 0; i < topPrices.NUM_PRICES; i++)
	{
		outFile << topPrices.name[i] << endl;
		outFile << topPrices.date[i] << endl;
		outFile << topPrices.price[i] << endl;
	}
}
void calcTopPrices(HighPrices& HighBTCPrices, CryptoRecord cryptos[], int NumCryptos) {
	

}


void sortTopPrices( HighPrices& topPrices)
{
	for (size_t j = 0; j < topPrices.NUM_PRICES; j++)
	{
		for (int i = 1; i < topPrices.NUM_PRICES; i++)
		{
			double tmpPrice = topPrices.price[i];
			string tmpName = topPrices.name[i];
			string tmpDate = topPrices.date[i];

			if (tmpPrice > topPrices.price[9])
			{
				topPrices.price[i - 1] = topPrices.price[i];
				topPrices.name[i - 1] = topPrices.name[i];
				topPrices.date[i - 1] = topPrices.date[i];
				topPrices.date[i] = tmpDate;
				topPrices.name[i] = tmpName;
				topPrices.price[i] = tmpPrice;
			}

		}
	}
}

void computeCryptoStats(CryptoStatData stats[], int& numStats, CryptoRecord Cryptos[], int numCoins) {

	int i = 0;
	numStats = 0;
	while (i < numCoins) {
		CryptoRecord c = Cryptos[i];

		stats[numStats].cryptoName = c.coinNames;
		while (c.coinNames == stats[numStats].cryptoName) {

			stats[numStats].totalRecords += 1;

			//add the incoming price to the running total for that crypto 
			stats[numStats].totalPrice += c.coinPrices;

			//make sure to update the min and max price for that crypto if warranted.
			// if the new price is less than the current minimum 
			if (c.coinPrices < stats[numStats].minPrice) {
				// update minimum to new price
				stats[numStats].minPrice = c.coinPrices;
			}
			//new max
			if (c.coinPrices > stats[numStats].maxPrice) {
				stats[numStats].maxPrice = c.coinPrices;
			}
			i++;
			// avoid memory error
			if (i >= numCoins) {
				break;
			}
			c = Cryptos[i];

		}

		numStats++;

	}
}


void writeCryptoStats(ofstream& outFile, CryptoStatData CryptoStats[], int numCryptos) {
	for (int i = 0; i < numCryptos; i++) {
		CryptoStatData c = CryptoStats[i];
		double avg = c.totalPrice / c.totalRecords;

		printMinMaxAvgForCoin(outFile, c.cryptoName, c.totalRecords, avg, c.minPrice, c.maxPrice);




	}
}

void writeCryptoData(ofstream& outFile, CryptoRecord Cryptos[], int numCoins) {


	printCoinRecords(outFile, Cryptos, numCoins);
	outFile << endl << "********************************************************************************" << endl;

	printMinMaxAvgPriceForEachCoin(outFile, Cryptos, numCoins);
	outFile << endl << "********************************************************************************" << endl;

	printNumDaysMarketCapIncreasedForEachCoin(outFile, Cryptos, numCoins);
	outFile << endl << "********************************************************************************" << endl;

	printHighestPriceIncreaseForEachCoin(outFile, Cryptos, numCoins);
	outFile << endl << "********************************************************************************" << endl;

	printHighestPricesForCoin(outFile, "Bitcoin", Cryptos, numCoins);
	outFile << endl << "********************************************************************************" << endl;

}


//Parse each field from a file line into struct array
//
//*Assumptions: 5 fields are in the format 
// Coin,Symbol,Date,Marketcap(USD),Price(USD)
void readCryptoData(ifstream& inFile, CryptoRecord cryptos[], int& numCoins, int max) {
	string fileLine;
	while (numCoins < max && getline(inFile, fileLine)) {
		if (fileLine != "") {

			int startPos = 0;
			int commaPos = -1;
			//CryptoRecord Cryptos;

			cryptos[numCoins].coinNames = getSubstrUpToNextComma(fileLine, startPos);
			cryptos[numCoins].coinSymbols = getSubstrUpToNextComma(fileLine, startPos);
			cryptos[numCoins].recordDates = getSubstrUpToNextComma(fileLine, startPos);
			cryptos[numCoins].marketCaps = stod(getSubstrUpToNextComma(fileLine, startPos));
			cryptos[numCoins].coinPrices = stod(getSubstrUpToNextComma(fileLine, startPos));
			numCoins++;
		}
	}

}

string getSubstrUpToNextComma(string str, int& startPos) {
	//Return the substring from a starting position (inclusive) until the
	//position of the first comma encountered (not inclusive of the comma). 
	//If there is no comma from the starting position onward, return the 
	//substring from the starting position until the end of the string.

	string substrUpToNextComma;

	int commaPos = str.find(",", startPos);

	if (commaPos == -1) {
		substrUpToNextComma = str.substr(startPos);
	}
	else {
		substrUpToNextComma = str.substr(startPos, commaPos - startPos);
	}

	//update the start position to be after the comma position
	//so that it is already set for the next call to this function
	startPos = commaPos + 1;

	return substrUpToNextComma;
}

void printCoinRecords(ofstream& outFile, CryptoRecord Cryptos[], int numRecords) {
	//Print the information for each coin record on one line per record

	for (int i = 0; i < numRecords; i++) {

		outFile << left;
		outFile << setw(21) << Cryptos[i].coinNames;
		outFile << setw(6) << Cryptos[i].coinSymbols;

		outFile << right;
		outFile << setw(13) << Cryptos[i].recordDates;

		outFile << fixed << setprecision(0);
		outFile << setw(20) << Cryptos[i].marketCaps;

		outFile << fixed << setprecision(4);
		outFile << setw(15) << Cryptos[i].coinPrices << endl;

	}
}


void printMinMaxAvgPriceForEachCoin(ofstream& outFile, CryptoRecord cryptos[], int numRecords) {
	//Print basic stats for each coin
	//*Assumptions: records are grouped by coin and sorted (ascending) by date within
	// each coin

	string curCoinName;
	int countOfCurrentCoin;
	double sumOfPrices;
	double minPrice;
	double maxPrice;
	double avgPrice;

	if (numRecords <= 0) {
		cout << "No records exist for which to analyze." << endl;
		return;
	}

	//Initialize statistics for first coin
	curCoinName = cryptos[0].coinNames;
	countOfCurrentCoin = 1;
	sumOfPrices = cryptos[0].coinPrices;
	minPrice = cryptos[0].coinPrices;
	maxPrice = cryptos[0].coinPrices;

	for (int i = 1; i < numRecords; i++) {
		//If the coin names are the same, keep aggregating the
		//statistical variables for that coin
		if (cryptos[i].coinNames == cryptos[i - 1].coinNames) {
			minPrice = min(minPrice, cryptos[i].coinPrices);
			maxPrice = max(maxPrice, cryptos[i].coinPrices);
			sumOfPrices += cryptos[i].coinPrices;
			countOfCurrentCoin++;
		}
		//Otherwise, print the statistics for the coin that just ended
		//and initialize the statical variables to start aggregating
		//for the new (current) coin
		else {
			avgPrice = sumOfPrices / countOfCurrentCoin;
			printMinMaxAvgForCoin(outFile, curCoinName, countOfCurrentCoin, avgPrice, minPrice, maxPrice);
			curCoinName = cryptos[i].coinNames;
			countOfCurrentCoin = 1;
			sumOfPrices = cryptos[i].coinPrices;
			minPrice = cryptos[i].coinPrices;
			maxPrice = cryptos[i].coinPrices;
		}
	}
	//print stats for last coin
	avgPrice = sumOfPrices / countOfCurrentCoin;
	printMinMaxAvgForCoin(outFile, curCoinName, countOfCurrentCoin, avgPrice, minPrice, maxPrice);
}

void printMinMaxAvgForCoin(ofstream& outFile, string curCoinName, int countOfCurrentCoin,
	double avgPrice, double minPrice, double maxPrice) {
	//Print stats to output file for a single coin
	outFile << endl;

	setprecisionBasedOnPrice(outFile, minPrice);

	outFile << curCoinName << endl;
	outFile << "---------------------------------------------------" << endl;
	outFile << " number of records: " << countOfCurrentCoin << endl;
	outFile << " min price     (USD $): " << setw(9) << minPrice << endl;
	outFile << " max price     (USD $): " << setw(9) << maxPrice << endl;
	outFile << " average price (USD $): " << setw(9) << avgPrice << endl;
}

double min(double a, double b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}

double max(double a, double b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

void printNumDaysMarketCapIncreasedForEachCoin(ofstream& outFile, CryptoRecord cryptos[], int numRecords) {
	//Print the number of days the market capitalization (i.e. overall market value) 
	//for each coin declined
	//
	//*Assumptions: records are grouped by coin and sorted (ascending) by date within
	// each coin

	int daysIncreased = 0;
	string curCoin;

	if (numRecords <= 0) {
		cout << "No records exist for which to analyze." << endl;
		return;
	}

	curCoin = cryptos[0].coinNames;

	outFile << endl;

	for (int i = 1; i < numRecords; i++) {
		if (cryptos[i].coinNames == cryptos[i - 1].coinNames) {
			if (cryptos[i].marketCaps < cryptos[i - 1].marketCaps) {
				daysIncreased++;
			}
		}
		else {
			outFile << "The market cap for " << curCoin << " increased " << daysIncreased << " days." << endl;
			curCoin = cryptos[i].coinNames;
			daysIncreased = 0;
		}
	}

	outFile << "The market cap for " << curCoin << " increased " << daysIncreased << " days." << endl;
}


void printHighestPriceIncreaseForEachCoin(ofstream& outFile, CryptoRecord cryptos[], int numRecords) {
	//Print the highest daily increase in price (in terms of USD) for each coin
	//Also print the percentage for said increase. 
	//
	//*Note that this function does NOT necessarily print the highest percentage 
	// increase. For instance, an increase from 100.00 to 102.00 represents a 
	// 2.00 (2%) increase, whereas an increase from 1.00 to 2.00 represents a 
	// 1.00 (100%) increase. This function would print the former rather than the 
	// latter since it has a higher absolute monetary increase
	//
	//**Assumptions: records are grouped by coin and sorted (ascending) by date within
	//  each coin
	double largestPriceIncreaseVal = numeric_limits<double>::min();
	double largestPriceIncreasePct = 0;
	string largestPriceIncreaseDateFrom = "N/A";
	string largestPriceIncreaseDateTo = "N/A";
	string curCoin;

	if (numRecords <= 0) {
		cout << "No records exist for which to analyze." << endl;
		return;
	}

	// in original:
	curCoin = cryptos[0].coinNames;


	outFile << fixed << setprecision(4);

	for (int i = 1; i < numRecords; i++) {
		if (cryptos[i].coinNames == cryptos[i - 1].coinNames) {
			double dailyPriceDiff = cryptos[i].coinPrices - cryptos[i - 1].coinPrices;

			if (dailyPriceDiff > largestPriceIncreaseVal) {
				largestPriceIncreaseVal = dailyPriceDiff;
				largestPriceIncreasePct = 100 * (largestPriceIncreaseVal / cryptos[i - 1].coinPrices);
				largestPriceIncreaseDateFrom = cryptos[i - 1].recordDates;
				largestPriceIncreaseDateTo = cryptos[i].recordDates;
			}
		}
		else {
			setprecisionBasedOnPrice(outFile, largestPriceIncreaseVal);

			// wrong:
			//printHighestPriceIncreaseForEachCoin(outFile, cryptos, numRecords);

			// original:
			printHighestPriceIncreaseForCoin(
				outFile, curCoin, largestPriceIncreaseVal, largestPriceIncreasePct,
				largestPriceIncreaseDateFrom, largestPriceIncreaseDateTo);



			curCoin = cryptos[i].coinNames;
			largestPriceIncreaseVal = numeric_limits<double>::min();
			largestPriceIncreasePct = 0;
			largestPriceIncreaseDateFrom = "N/A";
			largestPriceIncreaseDateTo = "N/A";
		}
	}
	setprecisionBasedOnPrice(outFile, largestPriceIncreaseVal);
	// wrong:
	//printHighestPriceIncreaseForEachCoin(outFile, cryptos, numRecords);

	// original:
	printHighestPriceIncreaseForCoin(
		outFile, curCoin, largestPriceIncreaseVal, largestPriceIncreasePct,
		largestPriceIncreaseDateFrom, largestPriceIncreaseDateTo);


}


void printHighestPriceIncreaseForCoin(ofstream& outFile, string coinName,
	double val, double pct,
	string dateFrom, string dateTo) {
	//Handle the actual output for the highest price of each coin

	outFile << endl;
	outFile << "The largest USD price increase for " << coinName << ":" << endl;
	outFile << " " << val << " (" << fixed << setprecision(1) << pct << "%)" <<
		" USD increase occured between " << dateFrom << " and " << dateTo << endl;
}






void printHighestPricesForCoin(ofstream& outFile, string coinToAnalyze, CryptoRecord cryptos[], int numRecords) {
	//Keep track of and print the 3 highest prices for a given coin
	int highestPriceIdx;
	int secondHighestPriceIdx;
	int thirdHighestPriceIdx;

	string curCoin;

	if (numRecords <= 0) {
		cout << "No records exist for which to analyze." << endl;
		return;
	}

	highestPriceIdx = 0;
	secondHighestPriceIdx = 0;
	thirdHighestPriceIdx = 0;

	for (int i = 1; i < numRecords; i++) {
		if (cryptos[i].coinNames == coinToAnalyze) {
			if (cryptos[i].coinPrices > cryptos[highestPriceIdx].coinPrices) {
				thirdHighestPriceIdx = secondHighestPriceIdx;
				secondHighestPriceIdx = highestPriceIdx;
				highestPriceIdx = i;
			}
			else if (cryptos[i].coinPrices > cryptos[highestPriceIdx].coinPrices) {
				thirdHighestPriceIdx = secondHighestPriceIdx;
				secondHighestPriceIdx = i;
			}
			else if (cryptos[i].coinPrices > cryptos[highestPriceIdx].coinPrices) {
				thirdHighestPriceIdx = i;
			}
		}
	}

	setprecisionBasedOnPrice(outFile, cryptos[highestPriceIdx].coinPrices);

	outFile << endl;
	outFile << "The 3 highest USD prices and corresponding dates for " << coinToAnalyze << " are:" << endl;
	outFile << " 1) " << setw(11) << cryptos[highestPriceIdx].coinPrices
		<< " on " << cryptos[highestPriceIdx].recordDates << endl;

	//Ensure integrity if there are less records than we are ranking
	if (numRecords >= 2) {
		outFile << " 2) " << setw(11) << cryptos[secondHighestPriceIdx].coinPrices
			<< " on " << cryptos[secondHighestPriceIdx].recordDates << endl;
	}
	if (numRecords >= 3) {
		outFile << " 3) " << setw(11) << cryptos[thirdHighestPriceIdx].coinPrices
			<< " on " << cryptos[thirdHighestPriceIdx].recordDates << endl;
	}
}

void setprecisionBasedOnPrice(ofstream& outFile, double price) {
	//Typically coins with prices under a dollar give more decimal
	//places than 2, so show up to 4 decimal places in the statistical
	//results if this is the case
	if (price < 1.00) {
		outFile << fixed << setprecision(4);
	}
	else {
		outFile << fixed << setprecision(2);
	}
}
