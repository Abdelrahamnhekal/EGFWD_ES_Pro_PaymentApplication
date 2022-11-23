#include<stdio.h>
#include<string.h>
#include"terminal.h"
#include<time.h>_


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorStatus = TERMINAL_OK;
	time_t Time;
	Time = time(NULL);
	struct tm currentTime = *localtime(&Time);

	

	termData->transactionDate[0] = (currentTime.tm_mday / 10) + 48;
	
	termData->transactionDate[1] = (currentTime.tm_mday % 10) + 48;
	
	termData->transactionDate[2] = '/';
	termData->transactionDate[3] = ((currentTime.tm_mon + 1) / 10) + 48;
	
	termData->transactionDate[4] = ((currentTime.tm_mon + 1) % 10) + 48;
	
	termData->transactionDate[5] = '/';
	
	termData->transactionDate[6] = ((currentTime.tm_year + 1900) / 1000) + 48;
	

	termData->transactionDate[7] = ((currentTime.tm_year + 1900) / 100) - 10 * ((currentTime.tm_year + 1900) / 1000) + 48;
	
	termData->transactionDate[8] = ((currentTime.tm_year + 1900) / 10) - 100 * ((currentTime.tm_year + 1900) / 1000) + 48;
	
	termData->transactionDate[9] = ((currentTime.tm_year + 1900)) % 10 + 48;
	
	termData->transactionDate[10] = '\0';
	return ErrorStatus;
}
void getTransactionDateTest(void)
{
	ST_terminalData_t termData;
	getTransactionDate(&termData);
	printf("%s", termData.transactionDate);
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorStatus = TERMINAL_OK;
	//expire date MM/YY
	//terminal date DD/MM/YYYY
	uint8_t cardExpMonth;
	cardExpMonth = (cardData->cardExpirationDate[0] - 48) * 10 + (cardData->cardExpirationDate[1] - 48);
	uint8_t cardExpYear;
	cardExpYear = (cardData->cardExpirationDate[3] - 48) * 10 + (cardData->cardExpirationDate[4] - 48);
	uint8_t currentMonth;
	currentMonth = (termData->transactionDate[3] - 48) * 10 + (termData->transactionDate[4] - 48);
	uint8_t currentYear;
	currentYear = (termData->transactionDate[8] - 48) * 10 + (termData->transactionDate[9] - 48);


	if ((cardExpMonth < currentMonth && cardExpYear < currentYear) || cardExpYear < currentYear)
	{
		ErrorStatus = EXPIRED_CARD;
	}
	return ErrorStatus;
}
void isCardExpriedTest(void)
{
	ST_cardData_t cardData1 = { "AbdelrahmanMohamedGomma","1234567891234567","11/21" };
	ST_cardData_t cardData2 = { "AbdelrahmanMohamedGomma","1234567891234567","11/27" };
	ST_terminalData_t termData;
	getTransactionDate(&termData);
	printf("%s\n\n", termData.transactionDate);
	printf("#######################################################\n");
	printf("Tester Name: Abdelrahman Mohamed Hekal\n");
	printf("Function Name: isCardExpired\n");
	printf("Test Case 1: expired card \n");
	printf("Input Data: 11/21 \n");
	printf("Expected Result:2 (EXPIRED_CARD) \n");
	printf("Actual Result: %d \n", isCardExpired(&cardData1, &termData));
	printf("#######################################################\n");
	printf("Test Case 2: not expired card \n");
	printf("Input Data: 11/27 \n");
	printf("Expected Result:0 (TERMINAL_OK) \n");
	printf("Actual Result: %d \n", isCardExpired(&cardData2, &termData));

}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorStatus = TERMINAL_OK;
	float transactionAmount;


	printf("Enter transaction amount :");
	scanf_s("%f", &transactionAmount);
	if (transactionAmount <= 0)
	{
		ErrorStatus = INVALID_AMOUNT;
	}
	else
	{
		termData->transAmount = transactionAmount;

	}
	return ErrorStatus;
}
void getTransactionAmountTest(void)
{
	ST_terminalData_t termData;
	printf("#######################################################\n");
	printf("Tester Name:Abdelrahman Mohamed Hekal\n");
	printf("Function Name: getTransactionAmount\n");
	printf("Test Case 1: Negative value \n");
	printf("Actual Result: %d \n", getTransactionAmount(&termData));
	printf("Input Data: -5 \n");
	printf("Expected Result:4 (INVALID_AMOUNT) \n");
	printf("#######################################################\n");
	printf("Test Case 2: Zero value \n");
	printf("Actual Result: %d \n", getTransactionAmount(&termData));
	printf("Input Data: 0 \n");
	printf("Expected Result:4 (INVALID_AMOUNT) \n");
	printf("#######################################################\n");
	printf("Test Case 3: Positve value \n");
	printf("Actual Result: %d \n", getTransactionAmount(&termData));
	printf("Input Data: 5 \n");
	printf("Expected Result:0 (TEMINAL_OK) \n");
	printf("#######################################################\n");
	printf("Test Case 4: Positve Float value \n");
	printf("Actual Result: %d \n", getTransactionAmount(&termData));
	printf("Input Data: 155.3 \n");
	printf("Expected Result:0 (TEMINAL_OK) \n");

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorStatus = TERMINAL_OK;

	if (termData->transAmount > termData->maxTransAmount)
	{
		ErrorStatus = EXCEED_MAX_AMOUNT;
	}
	return ErrorStatus;
}
void isBelowMaxAmountTest(void)
{
	ST_terminalData_t termData;
	//Max amount 10000
	termData.maxTransAmount = 10000;

	printf("#######################################################\n");
	printf("Tester Name: Abdelrahman Mohamed Hekal\n");
	printf("Function Name: isBelowMaxAmount\n");
	printf("Test Case 1: more than max amount (>10000)\n");
	termData.transAmount = 16500;
	printf("Actual Result: %d \n", isBelowMaxAmount(&termData));
	printf("Input Data: 16500 \n");
	printf("Expected Result:5  (EXCEED_MAX_AMOUNT) \n");
	printf("#######################################################\n");
	printf("Test Case 2: less than max amount (<10000)\n");
	termData.transAmount = 8000;
	printf("Actual Result: %d \n", isBelowMaxAmount(&termData));
	printf("Input Data: 8000 \n");
	printf("Expected Result:0  (TERMINAL_OK) \n");
	printf("#######################################################\n");
	printf("Test Case 3: equal to max amount (=10000)\n");
	termData.transAmount = 10000;
	printf("Actual Result: %d \n", isBelowMaxAmount(&termData));
	printf("Input Data: 10000 \n");
	printf("Expected Result:0  (TERMINAL_OK) \n");

}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorStatus = TERMINAL_OK;
	float maxAmount;
	printf("Enter max amount :");
	scanf_s("%f", &maxAmount);

	if (maxAmount <= 0)
	{
		ErrorStatus = INVALID_MAX_AMOUNT;
	}
	else
	{
		termData->maxTransAmount = maxAmount;
	}
	return ErrorStatus;
}
void setMaxAmountTest(void)
{

	ST_terminalData_t termData;

	printf("#######################################################\n");
	printf("Tester Name:Abdelrahman Mohamed Hekal\n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 1:negative number\n");
	printf("Actual Result: %d \n", setMaxAmount(&termData));
	printf("Input Data: -150 \n");
	printf("Expected Result: 6  (INVALID_MAX_AMOUNT) \n");
	printf("#######################################################\n");
	printf("Test Case 2: zero \n");
	printf("Actual Result: %d \n", setMaxAmount(&termData));
	printf("Input Data: 0 \n");
	printf("Expected Result: 6  (INVALID_MAX_AMOUNT) \n");
	printf("#######################################################\n");
	printf("Test Case 3: Positve number \n");
	printf("Actual Result: %d \n", setMaxAmount(&termData));
	printf("Input Data: 2300 \n");
	printf("Expected Result: 0  (TERMINAL_OK) \n");
	printf("#######################################################\n");
	printf("Test Case 4:Float Positve number \n");
	printf("Actual Result: %d \n", setMaxAmount(&termData));
	printf("Input Data: 13000.6 \n");
	printf("Expected Result: 0  (TERMINAL_OK) \n");

}
