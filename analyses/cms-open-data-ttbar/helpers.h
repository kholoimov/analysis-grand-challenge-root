#ifndef HELPERS
#define HELPERS

#include <random>
#include <string>
#include <algorithm>

#include "ROOT/RVec.hxx"
#include "TH1D.h"
#include "TRandom3.h"
#include <Math/Vector4D.h>

inline ROOT::RVecF jet_pt_resolution(const ROOT::RVecF &jet_pt)
{
   // normal distribution with 5% variations, shape matches jets
   ROOT::RVecF res(jet_pt.size());

   // The jet_pt is in GeV, so the first three digits after the comma are fairly random.
   double mean = 1.f;
   double sigma = 0.05f;
   for (std::size_t i = 0; i < jet_pt.size(); ++i) {
      res[i] = mean + ROOT::Math::gaussian_quantile(float(0.001 * (int(jet_pt[i] * 1000) % 1000)) + 0.0005, sigma);
   }

   return res;
}

inline float pt_scale_up()
{
   return 1.03;
}

inline ROOT::RVecF btag_weight_variation(const ROOT::RVecF &jet_pt)
{
   // weight variation depending on i-th jet pT (7.5% as default value, multiplied by i-th jet pT / 50 GeV)
   ROOT::RVecF res;
   res.reserve(std::min(4ul, jet_pt.size()));
   for (float pt : Take(jet_pt, 4))
   {
      res.push_back(1 + .075 * pt / 50);
      res.push_back(1 - .075 * pt / 50);
   }
   return res;
}

inline ROOT::RVecF flat_variation()
{
   // 2.5% weight variations
   return 1 + ROOT::RVecF({.025, -.025});
}

inline ROOT::RVec<ROOT::Math::PxPyPzMVector> ConstructP4 (const ROOT::RVecD & Pt, const ROOT::RVecD & Eta, const ROOT::RVecD & Phi, const ROOT::RVecD & M)
{

   return ROOT::VecOps::Construct<ROOT::Math::PxPyPzMVector>(
                ROOT::VecOps::Construct<ROOT::Math::PtEtaPhiMVector>(
                    Pt,
                    Eta,
                    Phi,
                    M
                )
          );
}

#endif
