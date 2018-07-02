#include <stdlib.h>
#include <stdio.h>

#define bili 0.3


// totalLoans:总贷款数
// rate: 年利率
// count: 还款期数
double getMonthPayment(double totalLoans, double rate,int count, int i){
    // 月利率
    double monthRate = rate / 12;
    double monthPayment = totalLoans / count + (totalLoans - i * totalLoans / count) * monthRate;
    return monthPayment;
}

double getMonthEarnings(int monthCount,double base,double rate){
    double monthRate = rate / 12;
    double monthEarnings = 0;
    for (int i = 0; i < monthCount ; i ++) {
        // 第i个月的收益
        
    }
    printf("\n----------------------华丽的分割线----------------------\n\n");
    printf("每个月%f元,%d月的累计收益是:%f\n",base,monthCount,monthEarnings);
    printf("\n----------------------华丽的分割线----------------------\n\n");
    return monthEarnings;
}

int main(int argc, char **argv){
    
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
    
    // 月利率
    double monthRate = rate / 12;
    
    double totalEarn = 0;
    for (int i = 0; i < monthCount; i ++) {
        // 第i月月供
        double pay = getMonthPayment(totalLoans * (1 - bili),loanRate,monthCount,i);
        printf("第%d月,月供是:%f\n",i,pay);
        totalEarn = totalEarn + totalEarn * monthRate + pay;
        printf ("如果理财,第%d月手里的钱是:%f\n",i,totalEarn);
    }
}
