#ifndef __MESSAGE_HASH_IMPL__
#define __MESSAGE_HASH_IMPL__

#include <string>
#include <memory>
#include <MessageHashAPI.h>

using messagePtr = std::unique_ptr<unsigned char> ; 
using charPtr = std::unique_ptr<char>;

class MessageHash_API MessageHashImpl
{
    public:        
        explicit MessageHashImpl();
        ~MessageHashImpl () = default; 

        void HashSha256 (const std::string&);
        void Hash(const std::string&, const std::string&); 
        messagePtr HashVal ();
        std::string hashValHex () ; 
        void printHash (); 
        std::string ListAvailableHash(); 
        

    private:
        MessageHashImpl (const MessageHashImpl&);
        MessageHashImpl& operator= (const MessageHashImpl&);
        MessageHashImpl(const MessageHashImpl&&);
        MessageHashImpl& operator= (const MessageHashImpl&&);
        

        messagePtr m_mPtr ; 
        unsigned int m_MessageHashLength; 

        charPtr m_Hashes ; 

};

#endif //ifndef __MESSAGE_HASH_IMPL
