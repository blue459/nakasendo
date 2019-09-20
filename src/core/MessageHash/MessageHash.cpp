#include <MessageHash/MessageHash.h>
#include <vector>
#include <MessageHash/MessageHashImpl.h>

MessageHash::MessageHash(): m_pImpl(new MessageHashImpl)
{
    return ; 
}

MessageHash::~MessageHash ()
{
    return ; 
}

void MessageHash::HashSha256(const std::string& msg)
{
    m_pImpl->HashSha256 (msg);
}

void MessageHash::Hash(const std::string& msg, const std::string& hashfunc)
{
    m_pImpl->Hash (msg, hashfunc);
}

void MessageHash::Hash(const std::vector<uint8_t>& msg,  const std::string& hashfunc){
    m_pImpl->Hash(msg, hashfunc);
}

std::unique_ptr<unsigned char[]> MessageHash::Value(){
    return m_pImpl->HashVal();
}

std::vector<uint8_t> MessageHash::HashValueBytes(){
    std::unique_ptr<unsigned char[]> val (Value());
    std::vector<uint8_t> ret;
    for(int i = 0; i<m_pImpl->HashLength(); ++i){
        ret.push_back(val[i]);
    }
    return ret;
}
std::string MessageHash::HashHex ()
{
    return (m_pImpl->hashValHex());
}

void MessageHash::printHash ()
{
    m_pImpl->printHash() ; 
}


std::string  MessageHash::ListAvailableHash ()
{
    return (m_pImpl->ListAvailableHash());
}

std::string HashMsgSHA256(const std::string& crMsg)
{
    MessageHash hashMess;
    hashMess.HashSha256 (crMsg);
    return hashMess.HashHex();
}