#include "customtype.h"
#include <vector>
#include <string>

std::vector<byte> ByteType::getBytes(){return this->bytes;}

void ByteType::setBytes(byte bytes[]){
    for(size_t i=0 ; i<this->size() ; i++)
        this->bytes[i] = bytes[i];
}

size_t ByteType::size(){return this->bytes.size();}

std::string ByteType::getHexString()
{
    constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                       '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    std::string s(this->size() * 2, ' ');
    for (size_t i = 0; i < this->size(); ++i) {
    s[2 * i]     = hexmap[(this->bytes[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[this->bytes[i] & 0x0F];
    }
    return s;
}
template <class T>
T CustomType<T>::get()
{
    T value;
    byte* buffer = (byte*)&value;

	for(size_t i=0 ; i<this->bytes.size() ; i++)
        if(this->littleEndian)
			buffer[i] = this->bytes[i];
        else
			buffer[i] = this->bytes[this->bytes.size() - i - 1];

    return value;
}

template <class T>
void CustomType<T>::set(T value)
{
    byte* buffer = (byte*)&value;

    for(size_t i=0 ; i<this->bytes.size() ; i++)
        if(this->littleEndian)
            this->bytes[i] = buffer[i];
        else
            this->bytes[i] = buffer[this->bytes.size() - i - 1];
}

Int24::Int24(bool littleEndian)
{
    this->bytes = std::vector<byte>(3,0);
    this->littleEndian = littleEndian;
}
Int24::Int24(int value, bool littleEndian) : Int24(littleEndian)
{
    this->set(value);
}

Int32::Int32(bool littleEndian)
{
    this->bytes = std::vector<byte>(4,0);
    this->littleEndian = littleEndian;
}
Int32::Int32(int value, bool littleEndian) : Int32(littleEndian)
{
    this->set(value);
}

Int64::Int64(bool littleEndian)
{
    this->bytes = std::vector<byte>(8,0);
    this->littleEndian = littleEndian;
}
Int64::Int64(long long int value, bool littleEndian) : Int64(littleEndian)
{
    this->set(value);
}

Float32::Float32(bool littleEndian)
{
    this->bytes = std::vector<byte>(4,0);
    this->littleEndian = littleEndian;
}
Float32::Float32(float value, bool littleEndian) : Float32(littleEndian)
{
    this->set(value);
}

Float64::Float64(bool littleEndian)
{
    this->bytes = std::vector<byte>(8,0);
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
    this->bytes = std::vector<byte>(value.size(),0);

    for(size_t i=0 ; i<this->size() ; i++)
        if(this->littleEndian)
			this->bytes[i] = (byte) value.at(i);
        else
			this->bytes[i] = (byte) value.at(this->bytes.size() - i - 1);
}
std::string Octetstring::get()
{
    char tempArr[this->size()];

    for(size_t i=0 ; i<this->bytes.size() ; i++)
        if(this->littleEndian)
			tempArr[i] = (char) this->bytes[i];
        else
			tempArr[i] = (char) this->bytes[this->bytes.size() - i - 1];

    std::string newString(tempArr);
    return newString;
}
