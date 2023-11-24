#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <iomanip>

using namespace std;

class Pair
{
public:
    virtual void add(int a, int b) = 0;
    virtual void sub(int a, int b) = 0;
    virtual void mul(int a, int b) = 0;
    virtual void div(int a, int b) = 0;
};

class Rotation: public Pair  // класс прямоугольника
{
private:
    int whole; //действительная часть
    int remainder; //мнимая часть
    
    long long *Reduce(long long partWhole, long long partRemainder)
    {
        long long *arrayReduceResult = new long long[2];
        
        arrayReduceResult[0] = partWhole;
        arrayReduceResult[1] = partRemainder;
        
        for (int i = 2; i < partRemainder + 1; i++)
        {
            if ((arrayReduceResult[0] % i == 0) && (arrayReduceResult[1] % i == 0))
            {
                arrayReduceResult[0] /= i;
                arrayReduceResult[1] /= i;
                i = 1;
            }
        }
        return arrayReduceResult;
    }
    
public:
    
    void InputElements()
    {
        long long booferWhole = 0;
        long long booferRemainder = 0;
        long long *arrayReduceResult = NULL;
        
        cin >> booferWhole >> booferRemainder;
        arrayReduceResult = Reduce(booferWhole, booferRemainder);
        
        whole = int(arrayReduceResult[0]);
        remainder = int(arrayReduceResult[1]);
        
        delete [] arrayReduceResult;
    }
    
    void DispleyRotations(int index)
    {
        cout << "Rational" << index << " (" << whole << '/' << remainder << ") ";
    }
    
    int GetWhole()
    {
        return whole;
    }
    
    int GetRemainder()
    {
        return remainder;
    }
    
    void Normalized(long long& firstWhole, long long& firstRemainder, long long& secondWhole, long long& secondRemainder)
    {
        long long kf = 0;

        if (firstRemainder % secondRemainder == 0)
        {
            kf = firstRemainder / secondRemainder;
            secondWhole *= kf;
            secondRemainder *= kf;
        }
        else if (secondRemainder % firstRemainder == 0)
        {
            kf = secondRemainder / firstRemainder;
            firstWhole *= kf;
            firstRemainder *= kf;
        }
        else
        {
            for(int i = 1;; i++)
            {
                if((i * firstRemainder) % secondRemainder == 0)
                {
                    kf = (i * firstRemainder) / secondRemainder;
                    firstWhole *= i;
                    firstRemainder *= i;
                    secondWhole *= kf;
                    secondRemainder *= kf;
                    break;
                }
            }
        }
    }
    
    void add(int a, int b)
    {
        long long secondWhole = a;
        long long secondRemainder = b;
        long long firstWhole = whole;
        long long firstRemainder = remainder;
        
        long long *arrayResul = NULL;
        
        Normalized(firstWhole, firstRemainder, secondWhole, secondRemainder);
        arrayResul = Reduce(firstWhole + secondWhole, firstRemainder);
        
        cout << '(' << arrayResul[0] << '/' << arrayResul[1] << ')' << endl;
        delete [] arrayResul;
    }
    
    void sub(int a, int b)
    {
        long long secondWhole = a;
        long long secondRemainder = b;
        long long firstWhole = whole;
        long long firstRemainder = remainder;
        
        long long *arrayResul = NULL;
        
        Normalized(firstWhole, firstRemainder, secondWhole, secondRemainder);
        
        arrayResul = Reduce(firstWhole - secondWhole, firstRemainder);

        cout << '(' << arrayResul[0] << '/' << arrayResul[1] << ')' << endl;
        delete [] arrayResul;

    }
    
    void mul(int a, int b)
    {
        long long secondWhole = a;
        long long secondRemainder = b;
        long long resWhole = whole * secondWhole;
        long long resRemainder = remainder * secondRemainder;
        long long *arrayResul = NULL;
        
        while (resWhole % 10 == 0 && resRemainder % 10 == 0)
        {
            resWhole /= 10;
            resRemainder /= 10;
        }
        arrayResul = Reduce(resWhole, resRemainder);
        
        resWhole = arrayResul[0];
        resRemainder = arrayResul[1];
        
        cout << '(' << resWhole << '/' << resRemainder << ')' << endl;
        delete [] arrayResul;
    }
    
    void div(int secondWhole, int secondRemainder)
    {
        long long resWhole = whole * secondRemainder;
        long long resRemainder = remainder * secondWhole;
        long long *arrayResul = NULL;
        
        while (resWhole % 10 == 0 && resRemainder % 10 == 0)
        {
            resWhole /= 10;
            resRemainder /= 10;
        }
        arrayResul = Reduce(resWhole, resRemainder);
        
        resWhole = arrayResul[0];
        resRemainder = arrayResul[1];
        
        cout << '(' << resWhole << '/' << resRemainder << ')' << endl;
        delete [] arrayResul;
    }
};

class Complex: public Pair  // класс прямоугольника
{
private:
    int valid; //действительная часть valid
    int imaginary; //мнимая часть imaginary
    
public:
    
    void InputComplexElements()
    {
        cin >> valid >> imaginary;
    }
    
    void DispleyComplex(int index)
    {
        cout << "Complex" << index << " (" << valid << "+i*" << imaginary << ") ";
    }
    
    int GetValid()
    {
        return valid;
    }
    
    int GetImaginary()
    {
        return imaginary;
    }
    
    void add(int secondValid, int secondImaginary)
    {
        cout << '(' << valid + secondValid << "+i*" << imaginary + secondImaginary << ')' << endl;
    }
    
    void sub(int secondValid, int secondImaginary)
    {
        cout << '(' << valid - secondValid << "+i*" << imaginary - secondImaginary << ')' << endl;
    }
    
    void mul(int secondValid, int secondImaginary)
    {
        cout << '(' << valid * secondValid - imaginary * secondImaginary << "+i*" << valid * secondImaginary + imaginary * secondValid << ')' << endl;
    }
    
    void div(int secondValid, int secondImaginary)
    {
        cout << '(' << (valid * secondValid + imaginary * secondImaginary) / (pow(secondValid, 2) + pow(secondImaginary, 2)) << "+i*";
        cout << (imaginary * secondValid - valid * secondImaginary) / (pow(secondValid, 2) + pow(secondImaginary, 2)) << ')' << endl;
    }
};

void RotationOperations(Rotation Object_1, Rotation Object_2)
{
    int secondWhole = Object_2.GetWhole();
    int secondRemainder = Object_2.GetRemainder();
    
    Object_1.DispleyRotations(1);
    Object_2.DispleyRotations(2);
    
    cout << endl << "Rational1+Rational2 ";
    Object_1.add(secondWhole, secondRemainder);
    
    cout << "Rational1-Rational2 ";
    Object_1.sub(secondWhole, secondRemainder);
    
    cout << "Rational1*Rational2 ";
    Object_1.mul(secondWhole, secondRemainder);
    
    cout << "Rational1/Rational2 ";
    Object_1.div(secondWhole, secondRemainder);
}


void ComplexOperations(Complex Elem_1, Complex Elem_2)
{
    int secondValid = Elem_2.GetValid();
    int secondImaginary = Elem_2.GetImaginary();
    
    Elem_1.DispleyComplex(1);
    Elem_2.DispleyComplex(2);
    
    cout << endl << "Complex1+Complex2 ";
    Elem_1.add(secondValid, secondImaginary);
    
    cout << "Complex1-Complex2 ";
    Elem_1.sub(secondValid, secondImaginary);
    
    cout << "Complex1*Complex2 ";
    Elem_1.mul(secondValid, secondImaginary);
    
    cout << "Complex1/Complex2 ";
    Elem_1.div(secondValid, secondImaginary);
}

void Control(Rotation Object_1, Rotation Object_2, Complex Elem_1, Complex Elem_2)
{
    int comand = 0;
    
    do
    {
        cin >> comand;
        switch (comand) {
            case 1:
                Object_1.InputElements();
                RotationOperations(Object_1, Object_2);
                break;
            case 2:
                Object_2.InputElements();
                RotationOperations(Object_1, Object_2);
                break;
            case 3:
                Elem_1.InputComplexElements();
                ComplexOperations(Elem_1, Elem_2);
                break;
            case 4:
                Elem_2.InputComplexElements();
                ComplexOperations(Elem_1, Elem_2);
                break;
        }
    }
    while(comand != 0);
}

int main()
{
    Rotation Object_1, Object_2;
    Complex Elem_1, Elem_2;
    
    Object_1.InputElements();
    Object_2.InputElements();
    
    Elem_1.InputComplexElements();
    Elem_2.InputComplexElements();
    
    RotationOperations(Object_1, Object_2);
    ComplexOperations(Elem_1, Elem_2);
    
    Control(Object_1, Object_2, Elem_1, Elem_2);
    
    return 0;
}


