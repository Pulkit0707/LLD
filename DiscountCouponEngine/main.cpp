#include <bits/stdc++.h>
using namespace std;

class Coupon{
    public:
    virtual void applyDiscount()=0;
    virtual ~Coupon()=default;
};

class PercentageCoupon : public Coupon{
    int percentage;
    public:
    PercentageCoupon(int percentage):percentage(percentage){}
    void applyDiscount() override{
        cout<<"Applying "<<percentage<<"% discount"<<endl;
    }
};

class FixedAmountCoupon : public Coupon{
    int amount;
    public:
    FixedAmountCoupon(int amount):amount(amount){}
    void applyDiscount() override{
        cout<<"Applying fixed discount of "<<amount<<endl;
    }
};

class CouponFactory{
    public:
    static Coupon*getCoupon(string couponType,int value){
        if(couponType=="percentage"){
            return new PercentageCoupon(value);
        }
        if(couponType=="amount"){
            return new FixedAmountCoupon(value);
        }
        return nullptr;
    }
};

class CouponStrategy{
    public:
    virtual void greeting()=0;
    virtual ~CouponStrategy()=default;
};

class SeasonalCoupon:public CouponStrategy{
    string season;
    public:
    SeasonalCoupon(string season):season(season){}
    void greeting() override{
        cout<<"Discount for the season "<<season<<endl;
    }
};

class FestivalCoupon:public CouponStrategy{
    string festival;
    public:
    FestivalCoupon(string festival):festival(festival){}
    void greeting() override{
        cout<<"Discount for the festival "<<festival<<endl;
    }
};

class CouponContext: public CouponStrategy, public CouponFactory{
    CouponStrategy* couponType;
    CouponFactory* discountType;
    string name;
    public:
    CouponContext(CouponStrategy* couponType, CouponFactory* discountType, string name):couponType(couponType),discountType(discountType),name(name){}
};

class CouponService{
    int amount;
    CouponContext* coupon;
    public:
    CouponService(int amount,CouponContext* coupon):amount(amount),coupon(coupon){}
    void applyCoupon(){
        coupon->getCoupon();
        coupon->greeting();
    }
};

int main(){

}