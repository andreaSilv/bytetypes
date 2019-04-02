#include "customtype.h"
#include <vector>
#include <algorithm>
#include <string>

template <class T>
std::vector<byte> CustomType<T>::getBytes(){return this->bytes;}

template <class T>
void CustomType<T>::setBytes(byte bytes[]){
    for(size_t i=0 ; i<this->size() ; i++)
        this->bytes[i] = bytes[i];
}

template <class T>
size_t CustomType<T>::size(){return this->bytes.size();}

template <class T>
T CustomType<T>::get()
{
    T value;
    byte* buffer = (byte*)&value;

    for(size_t i=0 ; i<this->bytes.size() ; i++)
        buffer[i] = this->bytes[i];

    return value;
}
template <class T>
void CustomType<T>::set(T value)
{
    byte* buffer = (byte*)&value;
    for(size_t i=0 ; i<this->bytes.size() ; i++)
        this->bytes[i] = buffer[i];
}

template <class T>
std::string CustomType<T>::getHexString()
{
    constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                       '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    std::string s(this->size() * 2, ' ');
    for (int i = 0; i < this->size(); ++i) {
    s[2 * i]     = hexmap[(this->bytes[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[this->bytes[i] & 0x0F];
    }
    return s;
}

Int24::Int24(bool littleEndian)
{
    this->bytes = std::vector<byte>(3);
    this->littleEndian = littleEndian;
}
Int24::Int24(int value, bool littleEndian) : Int24(littleEndian)
{
    this->set(value);
}

Int32::Int32(bool littleEndian)
{
    this->bytes = std::vector<byte>(4);
    this->littleEndian = littleEndian;
}
Int32::Int32(int value, bool littleEndian) : Int32(littleEndian)
{
    this->set(value);
}

Int64::Int64(bool littleEndian)
{
    this->bytes = std::vector<byte>(8);
    this->littleEndian = littleEndian;
}
Int64::Int64(long long int value, bool littleEndian) : Int64(littleEndian)
{
    this->set(value);
}

Float32::Float32(bool littleEndian)
{
    this->bytes = std::vector<byte>(4);
    this->littleEndian = littleEndian;
}
Float32::Float32(float value, bool littleEndian) : Float32(littleEndian)
{
    this->set(value);
}

Float64::Float64(bool littleEndian)
{
    this->bytes = std::vector<byte>(8);
    this->littleEndian = littleEndian;
}
Float64::Float64(double value, bool littleEndian) : Float64(littleEndian)
{
    this->set(value);
}

Octetstring::Octetstring(bool littleEndian)
{
    this->bytes = std::vector<byte>();
    this->littleEndian = littleEndian;
}
Octetstring::Octetstring(std::string value, bool littleEndian) : Octetstring(littleEndian)
{
    this->set(value);
}
void Octetstring::set(std::string value)
{
    this->bytes.clear();
    for(char i : value)
    {
        this->bytes.insert(this->bytes.begin(), (byte)i);
    }

    if(!this->littleEndian)
    {
        std::reverse(this->bytes.begin(), this->bytes.end());
    }
}
std::string Octetstring::get()
{
    std::string newString((char*) &(this->bytes[0]));
    return newString;
}
