class Train {
private:
    int trainID;
    bool isThroughTrain;

public:
    Train(int id, bool isThrough) : trainID(id), isThroughTrain(isThrough) {}

    int getTrainID() const {
        return trainID;
    }

    bool isThrough() const {
        return isThroughTrain;
    }
};
