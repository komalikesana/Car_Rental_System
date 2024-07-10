#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Car{
private:
    int id;
    string model;
    string brand;
    double costPerDay;
    bool booked;
public:
    Car(int id,string model,string brand,double costPerDay)
        : id(id),model(model),brand(brand),costPerDay(costPerDay),booked(false) {}

    int getId()const{
        return id; 
    }
    string getModel()const{
        return model; 
    }
    string getBrand()const{ 
        return brand;
        }
    double getCostPerDay()const{ 
        return costPerDay;
        }
    bool isBooked()const{
        return booked; 
        }
    void book(){
        booked = true;
       }
    void release(){ 
        booked = false;
        }
};

class Customer{
private:
    string name;
    string contactNumber;
    string email;
public:
    Customer(string name,string contactNumber,string email)
        : name(name),contactNumber(contactNumber),email(email) {}

    string getName()const{
        return name;
        }
    string getContactNumber()const{
        return contactNumber;
        }
    string getEmail()const{
        return email; 
         }
};

class Rental {
    protected:
    Customer customer;
    string startDate;
    string endDate;
    double amount;
private:
    string returnDate;
    double extraAmount;
   virtual void calculateAmount() = 0;
public:
    Rental(Customer customer,string startDate,string endDate)
        :customer(customer),startDate(startDate),endDate(endDate),amount(0),extraAmount(0) {}

    void initialize(){
        calculateAmount();
    }

    Customer getCustomer()const{
        return customer;
        }
    string getStartDate()const{
        return startDate;
        }
    string getEndDate()const{
        return endDate; 
    }
    double getAmount()const{
        return amount;
        }
    double getExtraAmount()const{
        return extraAmount;
        }
    string getReturnDate()const{
        return returnDate;
        }
    void setReturnDate(string date){
        returnDate = date;
        }
    void setExtraAmount(double amount){
        extraAmount = amount;
        }
};

class CarBooking : public Rental {
public:
    CarBooking(Customer customer,Car car,string startDate,string endDate)
        : Rental(customer,startDate,endDate),car(car) {
        initialize();
    }
    Car getCar()const{
        return car;
        }

private:
    Car car;
     void calculateAmount() override {
        int totalDays=1;
        if(endDate!=startDate) {
            totalDays=1+stoi(endDate.substr(8, 2))-stoi(startDate.substr(8, 2));
        }
        amount=totalDays*car.getCostPerDay();
    }
};

class CarBookingSystem {
    private:
    vector<Car> cars;
    vector<CarBooking> bookings;
    
    static string getCurrentDate() {
        return "2023-12-01";
    }
    
public:
    void addCar(Car car){
        cars.push_back(car);
        }
    void displayAvailableCars() {
        cout<<"Available Cars:"<< endl;
        for(const Car& car : cars){
            cout<<"ID:"<<car.getId()<<", Brand:"<<car.getBrand()<<", Model:"<<car.getModel()
                 <<", Cost per day: Rs."<<car.getCostPerDay();
            if(car.isBooked()){
                cout<<"(Booked)";
            } 
            else{
                cout<<"(Available for booking)";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    void bookCar(string name,string contactNumber,string email,int carId,string startDate,string endDate) {
        for(Car& car : cars){
            if(car.getId()==carId && !car.isBooked()){
                car.book();
                Customer customer(name, contactNumber, email);
                CarBooking booking(customer, car, startDate, endDate);
                bookings.push_back(booking);
                cout<<"Booking successful! Amount to be paid: Rs."<< booking.getAmount()<<endl;
                cout<<"Please go to the Transaction Section and pay amount and receive the car."<<endl;
                return;
            }
        }
        cout<<"Car not available for booking."<<endl;
    }

    void returnCar(int carId){
        for(CarBooking& booking:bookings){
            if(booking.getCar().getId()==carId&&booking.getEndDate()>getCurrentDate()){
                cout<<"Enter return date (YYYY-MM-DD): ";
                string returnDate;
                cin>>returnDate;
               booking.setReturnDate(returnDate);
                int extraDays=stoi(returnDate.substr(8, 2)) - stoi(booking.getEndDate().substr(8, 2));
                booking.setExtraAmount(extraDays*booking.getCar().getCostPerDay());
                  if(extraDays>0){
                    double fineAmount=100.0+booking.getExtraAmount();
                    cout<<"Car returned late on "<<returnDate <<". Fine to be paid: Rs."<< fineAmount<<endl;
                } 
                else{
                    cout<<"Car returned on time. No fine to be paid."<<endl;
                }
                for(Car& car:cars){
                    if(car.getId()==carId){
                        car.release();
                        break;
                    }
                }
                return;
            }
        }
        cout<<"Car not found, not booked, or already returned."<< endl;
    }

};

int main(){
    CarBookingSystem carSystem;
    carSystem.addCar(Car(1, "Thar", "Mahindra", 1200));
    carSystem.addCar(Car(2, "Innova", "Toyota", 2000));
    carSystem.addCar(Car(3, "XUV100", "Suzuki", 1000));
    carSystem.addCar(Car(4, "Hondacity", "Honda", 3200));
    carSystem.addCar(Car(5, "Hatchback", "Hyundai", 4000));
    carSystem.addCar(Car(6, "Focus", "Ford",3000));
    carSystem.addCar(Car(7, "Kiaseltos", "Kia", 1500));
    carSystem.addCar(Car(8, "AltraZ", "Tata", 2800));
    carSystem.addCar(Car(9, "F-Type", "Jaguar", 12000));
    carSystem.addCar(Car(10, "Renault KWID", "Renault", 3000));
    cout<<"*** Welcome to Car Rental Service ***"<<endl;
    int ch;
    do {
        cout<<"1. Display available cars"<<endl;
        cout<<"2. Book a car"<<endl;
        cout<<"3. Return a car"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Choose an option:"<<endl;
        cin>>ch;
        switch(ch){
            case 1:
                carSystem.displayAvailableCars();
                break;
            case 2: {
                string customerName, contactNumber, email;
                int selectedCarId;
                string startDate, endDate;
                cin.ignore(); 
                cout<<"Enter your name: ";
                getline(cin, customerName);
                cout<<"Enter your contact number: ";
                getline(cin, contactNumber);
                cout<<"Enter your email: ";
                getline(cin, email);
                cout<<"Enter the car ID you want to book: ";
                cin>>selectedCarId;
                cout<<"Enter start date (YYYY-MM-DD): ";
                cin>>startDate;
                cout<<"Enter end date (YYYY-MM-DD): ";
                cin>>endDate;
                carSystem.bookCar(customerName, contactNumber, email, selectedCarId, startDate, endDate);
                break;
            }
            case 3:{
                int returnCarId;
                cout<<"Enter the car ID you want to return: ";
                cin>>returnCarId;
                carSystem.returnCar(returnCarId);
                break;
            }
            case 4:
                cout<<"Exiting the program."<<endl;
                cout<<"** ThankYou for choosing us. **"<<endl;
                break;
            default:
                cout<<"Invalid choice. Please try again."<< endl;
                break;
        }
    } while (ch != 4);
} 