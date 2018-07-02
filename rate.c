#include <stdlib.h>
#include <stdio.h>

#define bili 0.3

// totalLoans:总贷款数
// rate: 年利率
// count: 还款期数
double getMonthPayment(double totalLoans, double rate,int count){
    // 月利率
    double monthRate = rate / 12;
    double base = 1;
    for (int i = 0; i < count; i ++) {
        base *= 1 + monthRate;
    }
    double monthPayment = totalLoans * monthRate * base / (base - 1);
    return monthPayment;
}

void printLeftLoans(double totalLoans, double rate,int count){
    double monthRate = rate / 12;
    double own = totalLoans;
    double monthPayment = getMonthPayment(totalLoans,rate,count);
    for (int i = 0; i < count; i ++) {
        // 当月欠银行贷款
        own = own * (1 + monthRate) - monthPayment;
        printf("第%d个月还欠银行的贷款总额:%f\n",i + 1,own);
    }
}

// 首付如果投资得到的收益
double getTotal(int monthCount,double rate,double base){
    double itemTotal = base;
    double monthRate = rate / 12;
    // 到第year年时,这个月的本金存入银行的时间,按月计算
    int saveTime = monthCount;
    for (int j = 0; j < saveTime / 12; j ++) {
        itemTotal *=  (1 + rate);
    }
    itemTotal = itemTotal * monthRate * (saveTime % 12) + itemTotal;
    return itemTotal;
}

double getMonthEarnings(int monthCount,double base,double rate){
    double monthRate = rate / 12;
    double monthEarnings = 0;
    for (int i = 0; i < monthCount ; i ++) {
        double itemTotal = base;
        // 到第year年时,这个月的本金存入银行的时间,按月计算
        int saveTime = monthCount - i;
        for (int j = 0; j < saveTime / 12; j ++) {
            itemTotal *=  (1 + rate);
        }
        itemTotal = itemTotal * monthRate * (saveTime % 12) + itemTotal;
        monthEarnings += itemTotal;
    }
    printf("\n----------------------华丽的分割线----------------------\n\n");
    printf("每个月%f元,%d月的累计收益是:%f\n",base,monthCount,monthEarnings);
    printf("\n----------------------华丽的分割线----------------------\n\n");
    return monthEarnings;
}

int main(int argc,char **argv){
    if (argc != 5) {
        printf("usage:%s <时间(年)> <理财利率> <总房款> <房贷利率> \n",argv[0]);
        return 0;
    }
    // 时间
    int year = atoi(argv[1]);
    
    // 年收益率
    double rate = atof(argv[2]);
    
    // 总贷款
    double totalLoans = atof(argv[3]);
    
    // 贷款年利率
    double loanRate = atof(argv[4]);
    
    // 首付
    double origin = totalLoans * bili;
    
    // 月供次数
    int monthCount = year * 12;
    
    // 月供金额
    double base = getMonthPayment(totalLoans * (1 - bili),loanRate,monthCount);
    // 月利率
    double monthRate = rate / 12;
    
    double total = 0;
    
    for (int i = 0; i < monthCount ; i ++) {
        double itemTotal = base;
        // 到第year年时,这个月的本金存入银行的时间,按月计算
        int saveTime = i;
        for (int j = 0; j < saveTime / 12; j ++) {
            itemTotal *=  (1 + rate);
        }
        itemTotal = itemTotal * monthRate * (saveTime % 12) + itemTotal;
//        printf("第%d个月的本金%d个月后的本金利息和是%f\n",i,saveTime,itemTotal);
        total += itemTotal;
        double originTotal = getTotal(i + 1,rate,origin);
        printf("如果用首付和月供投资理财到第%d个月是:%f,---其中月供涨到:%f, 首付涨到:%f\n",i + 1,total + originTotal ,total,originTotal);
    }
    printf("\n----------------------华丽的分割线----------------------\n\n");
    printLeftLoans(totalLoans * (1 - bili),loanRate,monthCount);
    printf("\n----------------------华丽的分割线----------------------\n\n");
    double originTotal = getTotal(monthCount,rate,origin);
    printf("首付%d个月后的本金利息和:%f\n",monthCount,originTotal);
    printf("月供收益合计:%f\n",total);
    printf("如果不买房总收益合计:%f\n",(total + originTotal));
    printf("首付:%f,月供:%f\n",totalLoans * bili,base);
    getMonthEarnings(60,1800,rate);
    return 0;
}
