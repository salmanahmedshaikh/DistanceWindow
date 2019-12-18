#include <stdint.h>

class helperClass
{
    public:
        helperClass();
        virtual ~helperClass();

        static uint64_t timeSinceEpochMillisec();
        static uint64_t timeSinceEpochMicrosec();


    protected:

    private:
};
