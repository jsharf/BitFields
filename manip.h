#ifndef MANIP_H
#define MANIP_H

#include <cstdint>

// template params:
// first is the smallest type big enough to hold this bit field
// second is position (lsb) of the bitfield in the register
// third is the length of the bitfield in bits
template <typename T, uint8_t Pos, uint8_t Len>
struct Field
{
    uint32_t getMask() const
    {
        const uint32_t field = (1 << Len) - 1;
        return static_cast<T>(field); 
    }

    void setVal(const T& val)
    {
        const T mask = getMask();
        m_val = val & mask;
    }

    Field& operator=(const T& other)
    {
        setVal(other);
        return *this;
    }

    T m_val;
};

template <typename T, typename X, uint8_t Y, uint8_t Z> 
T _modify(T reg, Field<X, Y, Z> other)
{
    reg &= ~(static_cast<T>(other.getMask())) << Y;
    return (reg | static_cast<T>(other.m_val) << Y);
}

template <typename T, typename H>
T modify(T reg, H field)
{
    return _modify(reg, field);
}

template <typename T, typename Head, typename... Tail>
T modify(T reg, Head field, Tail... fields)
{
    return _modify(reg, field) | modify(reg, fields...);
}

template <typename T, typename X, uint8_t Y, uint8_t Z>
X extract(T reg, Field<X, Y, Z> other)
{
    return (reg >> Y) & static_cast<T>(other.getMask());
}

#endif // MANIP_H
