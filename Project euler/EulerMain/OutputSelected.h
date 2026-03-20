#ifndef OUTPUTSELECTED_H
#define OUTPUTSELECTED_H

// From 2026
// Just create an instance and send values to output(), and it will output them less and less the bigger the number gets
class OutputSelected
{
    public:
        OutputSelected();
        virtual ~OutputSelected();
        void output(unsigned long long num);
        bool shouldOutput(unsigned long long num);
    protected:

    private:
        void reset();
        bool firstOutput;
        unsigned long long nextOutput;
        unsigned long long pow, nextPow;

};

#endif // OUTPUTSELECTED_H
