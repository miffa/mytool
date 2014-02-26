
/*
typedef unsigned char  uint8_t;
typedef char  int8_t;
typedef unsigned int uint32_t;
typedef int int32_t;
*/

namespace base64{
#include <stdint.h>

class Base64Tool
{
    public:
        Base64Tool();
        Base64Tool(const Base64Tool& item)
        {
            ser_no_ = item.ser_no_ ;
        }
        ~Base64Tool(){};
        bool IsSame(const Base64Tool& item)
        {
            return item.ser_no_ == ser_no_;
        }
    private:
        int ser_no_;


};
/*
extern uint8_t base64EncodeChars[];
extern uint8_t base64DecodeChars[];

void SohuEncodeBase64(uint8_t *src, uint32_t src_len, uint8_t *dst, uint32_t *dst_len);

void SohuDecodeBase64(uint8_t *src, uint32_t src_len, uint8_t *dst, uint32_t *dst_len);

class Base64Tools
{


};
*/

}
