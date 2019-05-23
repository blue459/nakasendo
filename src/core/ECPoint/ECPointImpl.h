#ifndef __ECPOINT_IMPL_H__
#define __ECPOINT_IMPL_H__

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cctype>
#include <openssl/bn.h>
#include <openssl/objects.h>
#include <openssl/ec.h>

using namespace std;

typedef EC_POINT*  ECPOINT_ptr;
typedef EC_GROUP*  ECGROUP_ptr;
typedef EC_builtin_curve* EC_builtin_curve_ptr;

using CurveList = std::vector<std::pair<int, std::string>>;
using CTX_ptr = std::unique_ptr<BN_CTX, decltype(&::BN_CTX_free)>;

class ECPointImpl
{
    friend std::unique_ptr<ECPointImpl> Add(const ECPointImpl *obj1, const ECPointImpl *obj2);
    friend bool Compare(const ECPointImpl *obj1, const ECPointImpl *obj2);

    public:

        ECPointImpl() 
        { 
            m_gp = EC_GROUP_new_by_curve_name(NID_secp256k1);
            m_ec = EC_POINT_new(m_gp);
            m_nid = NID_secp256k1;
        }

        ECPointImpl(const int& nid) 
        {
            // Construct a builtin curve 
            if((m_gp = EC_GROUP_new_by_curve_name(nid)) == nullptr)
            {
                throw std::runtime_error("error : Failed to allocate curve");
            }
            m_ec = EC_POINT_new(m_gp);

            m_nid = nid;
        }

        ~ECPointImpl()
        {
            if (m_ec)
                EC_POINT_free(m_ec);

            if (m_gp)
                EC_GROUP_free(m_gp);

        }

        //
        ECPointImpl (const ECPointImpl& obj) 
        {
            m_gp = EC_GROUP_new_by_curve_name(obj.getNid()); 
            m_ec = EC_POINT_new(m_gp);         
            EC_POINT_copy (m_ec, obj.ec());
            m_nid = obj.getNid();
        }

        ECPointImpl& operator= (const ECPointImpl& obj)
        {
            if (this != &obj)
            {
                m_gp = EC_GROUP_new_by_curve_name(obj.getNid()); 
                m_ec = EC_POINT_new(m_gp);
                EC_POINT_copy (m_ec, obj.ec());
		        m_nid = obj.getNid();
            }
            return *this;
        }

        const ECPOINT_ptr ec () const { return m_ec;}
        const ECGROUP_ptr gp () const { return m_gp;}
        const int getNid() const { return m_nid;};

        // Invert the given object
        void Invert();

        // Check if the EC is at Infinity
        bool CheckInfinity();

        // Check if the EC is on the curve
        bool CheckOnCurve();

        // Multiply ECPoint with Hex number
        std::unique_ptr<ECPointImpl> MultiplyWithHexBigNum (const std::string& bn_obj_m, const std::string& bn_obj_n); 

        // Multiply ECPoint with dec number
        std::unique_ptr<ECPointImpl> MultiplyWithDecBigNum (const std::string& bn_obj_m, const std::string& bn_obj_n); 

	// Double the ECPointImpl
        std::unique_ptr<ECPointImpl> Double();

        std::string ToHex();
        bool FromHex(const std::string& hexStr, int nid);

        void SetRandom (); 
        std::pair<std::string, std::string> GetAffineCoords_GFp (); 

    private:

        ECPointImpl(const ECPOINT_ptr& ec, const ECGROUP_ptr& gp, const int& nid) 
        {
            m_gp = EC_GROUP_new_by_curve_name(nid);
            m_ec = EC_POINT_new(m_gp); 
            EC_POINT_copy (m_ec, ec);
            m_nid = nid; 
        }

        std::unique_ptr<ECPointImpl> Multiply(BIGNUM *m_ptr, BIGNUM *n_ptr = nullptr);

        ECPOINT_ptr m_ec = nullptr; 
        ECGROUP_ptr m_gp = nullptr; 
        int m_nid = 0;
};

CurveList  _getCurveList();
#endif // __ECPOINT_IMPL_H__