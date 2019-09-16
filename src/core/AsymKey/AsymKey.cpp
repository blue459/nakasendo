#include <AsymKey/AsymKey.h>
#include <AsymKey/AsymKeyImpl.h>

#include <BigNumbers/BigNumbers.h>
#include <SecretSplit/KeyShare.h>

AsymKey::~AsymKey() = default;
AsymKey::AsymKey(AsymKey&& obj) noexcept = default;
AsymKey& AsymKey::operator=(AsymKey&& obj) noexcept = default;
AsymKey::AsymKey(const AsymKey& obj)
: m_pImpl(new AsymKeyImpl(*obj.m_pImpl))
{
}

AsymKey& AsymKey::operator=(const AsymKey& obj)
{
    if (this != &obj)
    {
        m_pImpl.reset(new AsymKeyImpl(*obj.m_pImpl));
    }
    return *this;
}

AsymKey::AsymKey() : m_pImpl(new AsymKeyImpl())
{
}

AsymKey::AsymKey(int groupNID) : m_pImpl(new AsymKeyImpl(groupNID))
{
}

bool AsymKey::is_valid() const
{
    return m_pImpl->is_valid();
}

int AsymKey::GroupNid()const
{
    return m_pImpl->GroupNid();
}
std::string AsymKey::Group_G_x() const
{
    return m_pImpl->Group_G_x();
}
std::string AsymKey::Group_G_y() const
{
    return m_pImpl->Group_G_y();
}
std::string AsymKey::Group_p() const
{
    return m_pImpl->Group_p();
}
std::string AsymKey::Group_a() const
{
    return m_pImpl->Group_a();
}
std::string AsymKey::Group_b() const
{
    return m_pImpl->Group_b();
}
std::string AsymKey::Group_n() const
{
    return m_pImpl->Group_n();
}

std::pair<std::string, std::string> AsymKey::getPublicKeyHEX() const
{
    return m_pImpl->getPublicKeyHEX();
}

std::string AsymKey::getPublicKeyHEXStr()  const
{
    return m_pImpl->getPublicKeyHEXStr();
}

std::string AsymKey::getPrivateKeyHEX() const
{
    return m_pImpl->getPrivateKeyHEXStr();
}

std::string AsymKey::getPublicKeyPEM()  const
{
    return m_pImpl->getPublicKeyPEMStr();
}

std::string AsymKey::getPrivateKeyPEM() const
{
    return m_pImpl->getPrivateKeyPEMStr();
}

std::string AsymKey::getPrivateKeyPEMEncrypted( const std::string& passphrase ) const
{
    return m_pImpl->getPrivateKeyPEMEncrypted( passphrase );
}

void AsymKey::setPrivateKeyPEMEncrypted( const std::string& encryptedPEM, const std::string& passphrase )
{
    return m_pImpl->setPrivateKeyPEMEncrypted( encryptedPEM, passphrase ) ; 
}

void AsymKey::setPEMPrivateKey(const std::string& crPEMKey)
{
    m_pImpl->setPEMPrivateKey(crPEMKey);
}

void AsymKey::setHEXPrivateKey(const std::string& crHEXKey)
{
    m_pImpl->setHEXPrivateKey(crHEXKey);
}

std::string AsymKey::getSharedSecretHex(const std::string& crOtherPublicPEMKey) const
{
    return m_pImpl->getSharedSecretHex(crOtherPublicPEMKey);
}

AsymKey AsymKey::derive(const std::string& crAdditiveMsg) const
{
    AsymKey new_key(GroupNid());
    new_key.m_pImpl.reset(m_pImpl->derive_private(crAdditiveMsg));
    return std::move(new_key);
}

std::pair<std::string, std::string> AsymKey::sign(const std::string& crMsg)const
{
    return m_pImpl->sign(crMsg);
}

// split the key into multiple parts
std::vector<KeyShare> AsymKey::split (const int& minThreshold, const int& numShares){
    return m_pImpl->split (minThreshold, numShares);
}
// recover a key from multiple shares
void AsymKey::recover (const std::vector<KeyShare>& keyshares){
    m_pImpl->recover(keyshares);
}

bool verify(const std::string& crMsg, const std::string& crPublicKeyPEMStr, const std::pair<std::string, std::string>& rs)
{
    return impl_verify(crMsg,crPublicKeyPEMStr,rs);
}

std::string derive_pubkey(const std::string& crPubPEMkey, const std::string& crRandomMsg)
{
    return impl_derive_pubkey(crPubPEMkey, crRandomMsg);
}

std::pair<std::string, std::string> AsymKey_API pubkey_pem2hex(const std::string& crPubPEMkey)
{
    return impl_pubkey_pem2hex(crPubPEMkey);
}
