
class queries
{
    public:
        queries();
        virtual ~queries();

        void trajectoriesCount();
        void filteredTrajectoriesCount(int trajLowerBound, int trajUpperBound);
        void filteredTrajectoriesLength(int trajLowerBound, int trajUpperBound);

    protected:

    private:
};
