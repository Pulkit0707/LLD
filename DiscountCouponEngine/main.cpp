#include <bits/stdc++.h>
using namespace std;

//================ Coupon ===================

class Coupon{
public:
    virtual int applyDiscount(int amount)=0;
    virtual ~Coupon()=default;
};

class PercentageCoupon : public Coupon{

    int percentage;

public:

    PercentageCoupon(int percentage):percentage(percentage){}

    int applyDiscount(int amount) override{

        cout<<"Applying "<<percentage<<"% discount"<<endl;

        return amount-(amount*percentage)/100;
    }
};

class FixedAmountCoupon : public Coupon{

    int discount;

public:

    FixedAmountCoupon(int discount):discount(discount){}

    int applyDiscount(int amount) override{

        cout<<"Applying fixed discount of "<<discount<<endl;

        return amount-discount;
    }
};

//================ Factory ===================

class CouponFactory{

public:

    static Coupon* getCoupon(string couponType,int value){

        if(couponType=="percentage")
            return new PercentageCoupon(value);

        if(couponType=="amount")
            return new FixedAmountCoupon(value);

        return nullptr;
    }
};

//================ Strategy ===================

class CouponStrategy{

public:

    virtual void greeting()=0;

    virtual ~CouponStrategy()=default;
};

class SeasonalCoupon : public CouponStrategy{

    string season;

public:

    SeasonalCoupon(string season):season(season){}

    void greeting() override{

        cout<<"Seasonal Offer : "<<season<<endl;
    }
};

class FestivalCoupon : public CouponStrategy{

    string festival;

public:

    FestivalCoupon(string festival):festival(festival){}

    void greeting() override{

        cout<<"Festival Offer : "<<festival<<endl;
    }
};

//================ Context ===================

class CouponContext{

    Coupon* coupon;

    CouponStrategy* strategy;

    string name;

public:

    CouponContext(Coupon* coupon,
                  CouponStrategy* strategy,
                  string name)
        :coupon(coupon),
         strategy(strategy),
         name(name){}

    int applyCoupon(int amount){

        cout<<"Coupon Name : "<<name<<endl;

        strategy->greeting();

        return coupon->applyDiscount(amount);
    }
};

//================ Service ===================

class CouponService{

    int amount;

    CouponContext* coupon;

public:

    CouponService(int amount,
                  CouponContext* coupon)
        :amount(amount),
         coupon(coupon){}

    void applyCoupon(){

        int finalAmount=coupon->applyCoupon(amount);

        cout<<"Original Amount : "<<amount<<endl;

        cout<<"Final Amount : "<<finalAmount<<endl;
    }
};

//================ Main ===================

int main(){

    Coupon* c1=CouponFactory::getCoupon("percentage",20);

    CouponStrategy* s1=new FestivalCoupon("Diwali");

    CouponContext* context=
        new CouponContext(c1,s1,"DIWALI20");

    CouponService service(1000,context);

    service.applyCoupon();

    return 0;
}