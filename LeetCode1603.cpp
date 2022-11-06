class ParkingSystem01 {
public:
    ParkingSystem(int big, int medium, int small) {
        _big = big; _medium = medium; _small = small;
    }
    
    bool addCar(int carType) {
        return ((carType == 1 && _big-- > 0) || (carType == 2 && _medium-- > 0) || (carType == 3 && _small-- > 0));
    }
    
private:
    int _big; int _medium; int _small;
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
