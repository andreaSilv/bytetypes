#include <vector>
#include <string>

typedef unsigned char byte;

class ByteType
{
protected:
    bool littleEndian;
    std::vector<byte> bytes;
public:
    virtual std::vector<byte> getBytes();
    virtual void setBytes(byte bytes[]);
    virtual size_t size();
    virtual std::string getHexString();
};

template <class T>
class CustomType : public ByteType
{
public:
    virtual T get();
    virtual void set(T value);
};

class Int24 : public CustomType<int>
{
public:
    Int24(bool littleEndian);
    Int24(int value, bool littleEndian);
};

class Int32 : public CustomType<int>
{
public:
    Int32(bool littleEndian);
    Int32(int value, bool littleEndian);
};

class Int64 : public CustomType<long long int>
{
public:
    Int64(bool littleEndian);
    Int64(long long int value, bool littleEndian);
};

class Float32 : public CustomType<float>
{
public:
    Float32(bool littleEndian);
    Float32(float value, bool littleEndian);
};

class Float64 : public CustomType<double>
{
public:
    Float64(bool littleEndian);
    Float64(double value, bool littleEndian);
};


class Octetstring : public CustomType<std::string>
{
public:
    Octetstring(bool littleEndian);
    Octetstring(std::string value, bool littleEndian);
    void set(std::string value) override;
    std::string get() override;
};
