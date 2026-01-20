#include "Global.h"
#include "Cfg/HeroCfg.h"
#include "Cfg/PuzzleCfg.h"
#include "Cfg/TerrainCfg.h"
#include "Comp/GateComp.h"
#include "Comp/GrailComp.h"
#include "Comp/HeroComp.h"
#include "Comp/MonolithComp.h"
#include "Comp/ObeliskComp.h"
#include "Comp/ObjectComp.h"
#include "Comp/PlayerIdComp.h"
#include "Comp/PositionComp.h"
#include "Comp/TerrainComp.h"
#include "Comp/TextureComp.h"
#include "Comp/TownComp.h"
#include "Comp/WhirlpoolComp.h"
#include "Def/Def.h"
#include "Ent/Ent.h"
#include "Global/Global.h"
#include "H3mLoader/H3mObject.h"
#include "Pal/PlayerPal.h"
#include "Pcx/Pcx.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "Sys/gui/LevelUpSys.h"
#include "Window/Window.h"
#include "World/World.h"
#include "entt/entity/entity.hpp"
#include "entt/entity/fwd.hpp"
#include <cstdint>
#include <map>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

void loadPcx() {
  const auto loadCommon = []() {
    const std::vector<std::string> filePaths = {
        "TPMAGECS.pcx", "TPMAGE.pcx", "VWorld.pcx", "univbldg.pcx",
        "TPCASNEU.pcx", "PUZZLOGO.pcx", "PUZCAS00.pcx", "PUZCAS01.pcx",
        "PUZCAS02.pcx", "PUZCAS03.pcx", "PUZCAS04.pcx", "PUZCAS05.pcx",
        "PUZCAS06.pcx", "PUZCAS07.pcx", "PUZCAS08.pcx", "PUZCAS09.pcx",
        "PUZCAS10.pcx", "PUZCAS11.pcx", "PUZCAS12.pcx", "PUZCAS13.pcx",
        "PUZCAS14.pcx", "PUZCAS15.pcx", "PUZCAS16.pcx", "PUZCAS17.pcx",
        "PUZCAS18.pcx", "PUZCAS19.pcx", "PUZCAS20.pcx", "PUZCAS21.pcx",
        "PUZCAS22.pcx", "PUZCAS23.pcx", "PUZCAS24.pcx", "PUZCAS25.pcx",
        "PUZCAS26.pcx", "PUZCAS27.pcx", "PUZCAS28.pcx", "PUZCAS29.pcx",
        "PUZCAS30.pcx", "PUZCAS31.pcx", "PUZCAS32.pcx", "PUZCAS33.pcx",
        "PUZCAS34.pcx", "PUZCAS35.pcx", "PUZCAS36.pcx", "PUZCAS37.pcx",
        "PUZCAS38.pcx", "PUZCAS39.pcx", "PUZCAS40.pcx", "PUZCAS41.pcx",
        "PUZCAS42.pcx", "PUZCAS43.pcx", "PUZCAS44.pcx", "PUZCAS45.pcx",
        "PUZCAS46.pcx", "PUZCAS47.pcx",

        "Puzzle.pcx", "UNIVGREN.PCX", "UNIVGOLD.PCX", "UNIVRED.PCX",
        "TPCASCAS.pcx", "CRBKGCAS.pcx", "TOCSMAG1.pcx", "TOCSMAG2.pcx",
        "TOCSM301.pcx", "TOCSM401.pcx", "TOCSTAV1.pcx", "TOCSDKMS.pcx",
        "TOCSCAS1.pcx", "TOCSCAS2.pcx", "TOCSCAS3.pcx", "TOCSH101.pcx",
        "TOCSH201.pcx", "TOCSH301.pcx", "TOCSH401.pcx", "TOCSMRK1.pcx",
        "TOCSMRK2.pcx", "TOCSBLAK.pcx", "TOCSLT01.pcx", "TOCSGR1H.pcx",
        "TOCSGR2H.pcx", "TOCSDKMN.pcx", "TOCSCAVM.pcx", "TOCSTAV2.pcx",
        "TOCSHOLY.pcx", "TOCSPIK1.pcx", "TOCSCRS1.pcx", "TOCSGR1N.pcx",
        "TOCSSWD1.pcx", "TOCSMON1.pcx", "TOCSC101.pcx", "TOCSANG1.pcx",
        "TOCSPIK2.pcx", "TOCSCRS2.pcx", "TOCSGR2N.pcx", "TOCSSWD2.pcx",
        "TOCSMON2.pcx", "TOCSCAV2.pcx", "TOCSANG2.pcx", "TORMAG1.pcx",
        "TORMAG2.pcx", "TORMAG3.pcx", "TORMAG4.pcx", "TORMAG5.pcx",
        "TORTAV.pcx", "TORCAS1.pcx", "TORCAS3.pcx", "TORCAS2.pcx",
        "TORHAL1.pcx", "TORHAL2.pcx", "TORHAL3.pcx", "TORHAL4.pcx",
        "TORMRK1.pcx", "TORMRK2.pcx", "TORAID.pcx", "TORGAR1A.pcx",
        "TORDWF1H.pcx", "TORDWF2H.pcx", "TORGAR2A.pcx", "TORDWFT.pcx",
        "TORTRE1H.pcx", "TORTRE2H.pcx", "TORHOLY.pcx", "TORCEN1A.pcx",
        "TORDWF1.pcx", "TORELF1.pcx", "TORPEG1A.pcx", "TORTRE1.pcx",
        "TORUNI1.pcx", "TORDR1AA.pcx", "TORCEN2A.pcx", "TORDWF2.pcx",
        "TORELF2.pcx", "TORPEG2A.pcx", "TORTRE2.pcx", "TORUNI2.pcx",
        "TORDR2AA.pcx", "TBCSBACK.pcx", "TBRMBACK.pcx", "TBTWBACK.pcx",
        "TBINBACK.pcx", "TBNCBACK.pcx", "TBDNBACK.pcx", "TBSTBACK.pcx",
        "TBFRBACK.pcx", "TPSHIPBK.PCX", "TOWNQKGH.pcx", "ADSTATHR.pcx",
        "ADSTATCS.pcx", "SpelTrnL.pcx", "SpelTrnR.pcx", "DiBoxBck.pcx",
        "HPS000KN.pcx", "HPS001KN.pcx", "HPS002KN.pcx", "HPS003KN.pcx",
        "HPS004KN.pcx", "HPS005KN.pcx", "HPS006KN.pcx", "HPS007KN.pcx",

        "HPS008CL.pcx", "HPS009CL.pcx", "HPS010CL.pcx", "HPS011CL.pcx",
        "HPS012CL.pcx", "HPS013CL.pcx", "HPS014CL.pcx", "HPS015CL.pcx",

        "HPS016RN.pcx", "HPS017RN.pcx", "HPS018RN.pcx", "HPS019RN.pcx",
        "HPS020RN.pcx", "HPS021RN.pcx", "HPS022RN.pcx", "HPS023RN.pcx",

        "HPS024DR.pcx", "HPS025DR.pcx", "HPS026DR.pcx", "HPS027DR.pcx",
        "HPS028DR.pcx", "HPS029DR.pcx", "HPS030DR.pcx", "HPS031DR.pcx",

        "HPS032AL.pcx", "HPS033AL.pcx", "HPS034AL.pcx", "HPS035AL.pcx",
        "HPS036AL.pcx", "HPS037AL.pcx", "HPS038AL.pcx", "HPS039AL.pcx",

        "HPS040WZ.pcx", "HPS041WZ.pcx", "HPS042WZ.pcx", "HPS043WZ.pcx",
        "HPS044WZ.pcx", "HPS045WZ.pcx", "HPS046WZ.pcx", "HPS047WZ.pcx",

        "HPS048HR.pcx", "HPS049HR.pcx", "HPS050HR.pcx", "HPS051HR.pcx",
        "HPS052HR.pcx", "HPS053HR.pcx", "HPS054HR.pcx", "HPS055HR.pcx",

        "HPS056DM.pcx", "HPS057DM.pcx", "HPS058DM.pcx", "HPS059DM.pcx",
        "HPS060DM.pcx", "HPS061DM.pcx", "HPS062DM.pcx", "HPS063DM.pcx",

        "HPS064DK.pcx", "HPS065DK.pcx", "HPS066DK.pcx", "HPS067DK.pcx",
        "HPS068DK.pcx", "HPS069DK.pcx", "HPS070DK.pcx", "HPS071DK.pcx",

        "HPS072NC.pcx", "HPS073NC.pcx", "HPS074NC.pcx", "HPS075NC.pcx",
        "HPS076NC.pcx", "HPS077NC.pcx", "HPS078NC.pcx", "HPS079NC.pcx",

        "HPS080OV.pcx", "HPS081OV.pcx", "HPS082OV.pcx", "HPS083OV.pcx",
        "HPS084OV.pcx", "HPS085OV.pcx", "HPS086OV.pcx", "HPS087OV.pcx",

        "HPS088WL.pcx", "HPS089WL.pcx", "HPS090WL.pcx", "HPS091WL.pcx",
        "HPS092WL.pcx", "HPS093WL.pcx", "HPS094WL.pcx", "HPS095WL.pcx",

        "HPS096BR.pcx", "HPS097BR.pcx", "HPS098BR.pcx", "HPS099BR.pcx",
        "HPS100BR.pcx", "HPS101BR.pcx", "HPS102BR.pcx", "HPS103BR.pcx",

        "HPS104BM.pcx", "HPS105BM.pcx", "HPS106BM.pcx", "HPS107BM.pcx",
        "HPS108BM.pcx", "HPS109BM.pcx", "HPS110BM.pcx", "HPS111BM.pcx",

        "HPS112BS.pcx", "HPS113BS.pcx", "HPS114BS.pcx", "HPS115BS.pcx",
        "HPS116BS.pcx", "HPS117BS.pcx", "HPS118BS.pcx", "HPS119BS.pcx",

        "HPS120WH.pcx", "HPS121WH.pcx", "HPS122WH.pcx", "HPS123WH.pcx",
        "HPS124WH.pcx", "HPS125WH.pcx", "HPS126WH.pcx", "HPS127WH.pcx",

        "HPS000PL.pcx", "HPS001PL.pcx", "HPS002PL.pcx", "HPS003PL.pcx",
        "HPS004PL.pcx", "HPS005PL.pcx", "HPS006PL.pcx", "HPS007PL.pcx",

        "HPS000EL.pcx", "HPS001EL.pcx", "HPS002EL.pcx", "HPS003EL.pcx",
        "HPS004EL.pcx", "HPS005EL.pcx", "HPS006EL.pcx", "HPS007EL.pcx",

        "HPS130KN.pcx", "HPS000SH.pcx", "HPS128QC.pcx", "HPS003SH.pcx",
        "HPS004SH.pcx", "HPS005SH.pcx", "HPS006SH.pcx", "HPS007SH.pcx",
        "HPS009SH.pcx", "HPS008SH.pcx", "HPS001SH.pcx", "HPS131DM.pcx",

        "HPSRAND1.pcx", "HPSRAND6.pcx", "HPSXXX.pcx", "HPSYYY.pcx",

        "HPL000KN.pcx", "HPL001KN.pcx", "HPL002KN.pcx", "HPL003KN.pcx",
        "HPL004KN.pcx", "HPL005KN.pcx", "HPL006KN.pcx", "HPL007KN.pcx",

        // Cleric (CL)
        "HPL008CL.pcx", "HPL009CL.pcx", "HPL010CL.pcx", "HPL011CL.pcx",
        "HPL012CL.pcx", "HPL013CL.pcx", "HPL014CL.pcx", "HPL015CL.pcx",

        // Ranger (RN)
        "HPL016RN.pcx", "HPL017RN.pcx", "HPL018RN.pcx", "HPL019RN.pcx",
        "HPL020RN.pcx", "HPL021RN.pcx", "HPL022RN.pcx", "HPL023RN.pcx",

        // Druid (DR)
        "HPL024DR.pcx", "HPL025DR.pcx", "HPL026DR.pcx", "HPL027DR.pcx",
        "HPL028DR.pcx", "HPL029DR.pcx", "HPL030DR.pcx", "HPL031DR.pcx",

        // Alchemist (AL)
        "HPL032AL.pcx", "HPL033AL.pcx", "HPL034AL.pcx", "HPL035AL.pcx",
        "HPL036AL.pcx", "HPL037AL.pcx", "HPL038AL.pcx", "HPL039AL.pcx",

        // Wizard (WZ)
        "HPL040WZ.pcx", "HPL041WZ.pcx", "HPL042WZ.pcx", "HPL043WZ.pcx",
        "HPL044WZ.pcx", "HPL045WZ.pcx", "HPL046WZ.pcx", "HPL047WZ.pcx",

        // Knight (HR)
        "HPL048HR.pcx", "HPL049HR.pcx", "HPL050HR.pcx", "HPL051HR.pcx",
        "HPL052HR.pcx", "HPL053HR.pcx", "HPL054HR.pcx", "HPL055HR.pcx",

        // Demon Lord (DM)
        "HPL056DM.pcx", "HPL057DM.pcx", "HPL058DM.pcx", "HPL059DM.pcx",
        "HPL060DM.pcx", "HPL061DM.pcx", "HPL062DM.pcx", "HPL063DM.pcx",

        // Death Knight (DK)
        "HPL064DK.pcx", "HPL065DK.pcx", "HPL066DK.pcx", "HPL067DK.pcx",
        "HPL068DK.pcx", "HPL069DK.pcx", "HPL070DK.pcx", "HPL071DK.pcx",

        // Necromancer (NC)
        "HPL072NC.pcx", "HPL073NC.pcx", "HPL074NC.pcx", "HPL075NC.pcx",
        "HPL076NC.pcx", "HPL077NC.pcx", "HPL078NC.pcx", "HPL079NC.pcx",

        // Overlord (OV)
        "HPL080OV.pcx", "HPL081OV.pcx", "HPL082OV.pcx", "HPL083OV.pcx",
        "HPL084OV.pcx", "HPL085OV.pcx", "HPL086OV.pcx", "HPL087OV.pcx",

        // Warlock (WL)
        "HPL088WL.pcx", "HPL089WL.pcx", "HPL090WL.pcx", "HPL091WL.pcx",
        "HPL092WL.pcx", "HPL093WL.pcx", "HPL094WL.pcx", "HPL095WL.pcx",

        // Barbarian (BR)
        "HPL096BR.pcx", "HPL097BR.pcx", "HPL098BR.pcx", "HPL099BR.pcx",
        "HPL100BR.pcx", "HPL101BR.pcx", "HPL102BR.pcx", "HPL103BR.pcx",

        // Battle Mage (BM)
        "HPL104BM.pcx", "HPL105BM.pcx", "HPL106BM.pcx", "HPL107BM.pcx",
        "HPL108BM.pcx", "HPL109BM.pcx", "HPL110BM.pcx", "HPL111BM.pcx",

        // Beastmaster (BS)
        "HPL112BS.pcx", "HPL113BS.pcx", "HPL114BS.pcx", "HPL115BS.pcx",
        "HPL116BS.pcx", "HPL117BS.pcx", "HPL118BS.pcx", "HPL119BS.pcx",

        // Witch (WH)
        "HPL120WH.pcx", "HPL121WH.pcx", "HPL122WH.pcx", "HPL123WH.pcx",
        "HPL124WH.pcx", "HPL125WH.pcx", "HPL126WH.pcx", "HPL127WH.pcx",

        // Planeswalker (PL)
        "HPL000PL.pcx", "HPL001PL.pcx", "HPL002PL.pcx", "HPL003PL.pcx",
        "HPL004PL.pcx", "HPL005PL.pcx", "HPL006PL.pcx", "HPL007PL.pcx",

        // Elementalist (EL)
        "HPL000EL.pcx", "HPL001EL.pcx", "HPL002EL.pcx", "HPL003EL.pcx",
        "HPL004EL.pcx", "HPL005EL.pcx", "HPL006EL.pcx", "HPL007EL.pcx",

        // 特殊英雄
        "HPL130KN.pcx", "HPL000SH.pcx", "HPL128QC.pcx", "HPL003SH.pcx",
        "HPL004SH.pcx", "HPL005SH.pcx", "HPL006SH.pcx", "HPL007SH.pcx",
        "HPL009SH.pcx", "HPL008SH.pcx", "HPL001SH.pcx", "HPL131DM.pcx",
        "SpelTrnL.pcx", "SpelTrnR.pcx", "ADROLLVR.pcx"};
    for (auto filePath : filePaths) {
      Pcx pcx("./Data/H3bitmap.lod/" + filePath);
      Global::pcxCache[filePath] = std::vector<SDL_Texture *>{pcx.load()};
    }
  };
  const auto loadPal = []() {
    const std::vector<std::string> filePaths = {
        "GPuCrdiv.pcx", "TPGATE.pcx",   "OvCast.pcx",   "TPMrkCrS.pcx",
        "ALTRART2.pcx", "ALTARMON.pcx", "TPMrkReS.pcx", "TPMrkPtS.pcx",
        "TPMrkAbS.pcx", "TPMrkAsS.pcx", "APHLFTBK.PCX", "AdvMap.pcx",
        "AResBar.pcx",  "Sysopbck.pcx", "SpelBack.pcx", "ADVOPTS.pcx",
        "TPrcrt.pcx",   "GARRISON.PCX", "HeroScr4.pcx", "Trade2.pcx",
        "TPSHIP.PCX",   "townScrn.pcx", "TpTavern.pcx", "CrStkPu.pcx",
        "lvlupbkg.pcx", "UNIVERS1.PCX", "UNIVERS2.PCX"};
    for (auto filePath : filePaths) {
      Pcx pcx("./Data/H3bitmap.lod/" + filePath);
      std::vector<SDL_Texture *> v;
      v.resize(8);
      for (int i = 0; i < 8; ++i) {
        memcpy(&pcx.palette[224], &PlayerPal::palette[i][0],
               32 * sizeof(SDL_Color));
        v[i] = pcx.load();
      }
      Global::pcxCache[filePath] = v;
    }
  };
  loadCommon();
  loadPal();
}
void loadDef() {
  const auto loadCommon = []() {
    const std::vector<std::string> filePaths = {
        "AVA0001.def",        "AvWPike.def",        "TPMAGE1.DEF",
        "AVXwhrl0.def",       "AVLr15r0.def",       "AVLskul0.def",
        "AVLr08r0.def",       "AVLsh2r0.def",       "AVLroug2.def",
        "AVLr07r0.def",       "AVLr02r0.def",       "AVLr11r0.def",
        "AVLr10r0.def",       "AVLr14r0.def",       "AVLyuc30.def",
        "AVLyuc20.def",       "AVLyuc10.def",       "AVLroug1.def",
        "AvLRR05.def",        "AVLroug0.def",       "AVLman10.def",
        "AVLmtgn1.def",       "AVLlk3g0.def",       "AVLmd3r0.def",
        "AVLPNTR0.def",       "AvLRG04.def",        "AvLRG01.def",
        "AvLRG08.def",        "AVLmtgn5.def",       "AVLman40.def",
        "AVLf03g0.def",       "AvLRG06.def",        "AVLsh2g0.def",
        "AvLRG09.def",        "AVLfl6d0.def",       "AVLsh4g0.def",
        "AvLRG05.def",        "AvLRG02.def",        "AVLf06g0.def",
        "AVLf12g0.def",       "AVLf08g0.def",       "AVLPNTR4.def",
        "AVLmtgn2.def",       "AVLmtgn3.def",       "AVLmtgn4.def",
        "AVLman30.def",       "AVWmon5.def",        "AVWmon7.def",
        "AVWmon6.def",        "AVWmon3.def",        "AVWmon4.def",
        "AVLmtgr4.def",       "AVLmtgr6.def",       "AVLmtgr5.def",
        "AVXwelr0.def",       "AVSfntn0.def",       "AVTrndm0.def",
        "AVArnd1.def",        "AVArnd2.def",        "AVArnd4.def",
        "AVArnd3.def",        "AvXDenT.def",        "AVSgrdn0.def",
        "avlsh7r0.def",       "AVTwagn0.def",       "AVXmags0.def",
        "AVLf09g0.def",       "AVLf10g0.def",       "AVLmd2g0.def",
        "AVLf11g0.def",       "AVLf07g0.def",       "avlsh8r0.def",
        "AVLca2r0.def",       "avlsh4r0.def",       "avlsh5r0.def",
        "avlsh9r0.def",       "avlsh3r0.def",       "AVLca1r0.def",
        "AVLct1r0.def",       "AVLct3r0.def",       "avlsh6r0.def",
        "avlsh1r0.def",       "avlsh2r0.def",       "AVLsh1r0.def",
        "ICN6432.def",        "AVLsh3r0.def",       "AVLoc3g0.def",
        "AVLSPTR5.def",       "AVLSPTR1.def",       "AVLSPTR2.def",
        "AVLSPTR0.def",       "AVLsh6g0.def",       "AVLSPTR6.def",
        "AVLSPTR4.def",       "AVLSPTR3.def",       "AVLoc1g0.def",
        "AVLoc2g0.def",       "AVLct6g0.def",       "AVLct5g0.def",
        "AVLct4g0.def",       "AVLct2g0.def",       "AVLctrg0.def",
        "avlmtrf6.def",       "avlmtrf3.def",       "avlmtrf4.def",
        "avlmtrf2.def",       "avlmtrf5.def",       "avlmtrf1.def",
        "AVSaxis0.def",       "AVXpost0.def",       "IAM012.DEF",
        "IAM013.DEF",         "IAM014.DEF",         "IAM015.DEF",
        "SpellBon.def",       "OVBUTN3.def",        "OVBUTN1.def",
        "OVBUTN6.def",        "OVBUTN4.def",        "OVMINES.def",
        "OVSLOT.def",         "AVXmaps0.def",       "AVGrefg0.def",
        "SMBAL.DEF",          "SMTENT.DEF",         "SMCART.DEF",
        "AVGsieg0.def",       "avxfgld.def",        "ALTARMY.DEF",
        "ALTSACR.DEF",        "ALTART.DEF",         "ALTSACC.DEF",
        "AvXAltar.def",       "ALTSACR.DEF",        "ALTFILL.DEF",
        "ALTEMBK.DEF",        "iGPCrDiv.def",       "TPMRKBU1.DEF",
        "TPMRKBU3.DEF",       "TPMRKBU2.DEF",       "TPMRKBU4.DEF",
        "TPMRKBU5.DEF",       "TPMRKB.DEF",         "AvXOblK.def",
        "AvXOblG.def",        "AVMlean0.def",       "AVSclvg0.def",
        "APHLF1G.def",        "APHLF1Y.def",        "APHLF1R.def",
        "AVXhild0.def",       "AVXmerm0.def",       "AVXsirn0.def",
        "AVAflot0.def",       "AVXhutm0.def",       "AVXeyem0.def",
        "AVXstbl0.def",       "AVSlibr0.def",       "AVSmerc0.def",
        "AVXl1sh0.def",       "AVXl2sh0.def",       "SpellScr.def",
        "AVXl3sh0.def",       "AVSarna0.def",       "AVXsanc0.def",
        "AVXgyne0.def",       "AVXseeb0.def",       "AVStmpl0.def",
        "AVXfyth0.def",       "AvSMarl.def",        "AVXskds0.def",
        "adcfra.def",         "AVSring0.def",       "AvXRedW.def",
        "imrl82.def",         "AVXrlly0.def",       "ilck82.def",
        "AVSidol0.def",       "AVSgzbo0.def",       "AVSschm0.def",
        "AVSwar20.def",       "AVXmn2o0.def",       "AVXmx1b0.def",
        "AVXmn1b0.def",       "AVXmn2g0.def",       "AVSwtch0.def",
        "AVXprsn0.def",       "AVXtrek0.def",       "AVXschl0.def",
        "IVIEWCR2.DEF",       "IViewCr.DEF",        "CPKMAN.DEF",
        "CHALBD.DEF",         "CLCBOW.DEF",         "CHCBOW.DEF",
        "CGRIFF.DEF",         "CRGRIF.DEF",         "CSWORD.DEF",
        "CCRUSD.DEF",         "CMONKK.DEF",         "CZEALT.DEF",
        "CCAVLR.DEF",         "CCHAMP.DEF",         "CANGEL.DEF",
        "CRANGL.DEF",         "TBCSEXT2.def",       "TBCSMAGE.def",
        "TBCSMAG2.def",       "TBCSMAG3.def",       "TBCSMAG4.def",
        "TBCSTVRN.def",       "TBCSDOCK.def",       "TBCSCSTL.def",
        "TBCSCAS2.def",       "TBCSCAS3.def",       "TBCSHALL.def",
        "TBCSHAL2.def",       "TBCSHAL3.def",       "TBCSHAL4.def",
        "TBCSMARK.def",       "TBCSSILO.def",       "TBCSBLAK.def",
        "TBCSSPEC.def",       "TBCSHRD1.def",       "TBCSHRD2.def",
        "TBCSBOAT.def",       "TBCSEXT0.def",       "TBCSEXT1.def",
        "TBCSHOLY.def",       "TBCSDW_0.def",       "TBCSDW_1.def",
        "TBCSDW_2.def",       "TBCSDW_3.def",       "TBCSDW_4.def",
        "TBCSDW_5.def",       "TBCSDW_6.def",       "TBCSUP_0.def",
        "TBCSUP_1.def",       "TBCSUP_2.def",       "TBCSUP_3.def",
        "TBCSUP_4.def",       "TBCSUP_5.def",       "TBCSUP_6.def",
        "TBRMEXT2.def",       "TBRMMAGE.def",       "TBRMMAG2.def",
        "TBRMMAG3.def",       "TBRMMAG4.def",       "TBRMMAG5.def",
        "TBRMTVRN.def",       "TBRMCSTL.def",       "TBRMCAS2.def",
        "TBRMCAS3.def",       "TBRMHALL.def",       "TBRMHAL2.def",
        "TBRMHAL3.def",       "TBRMHAL4.def",       "TBRMMARK.def",
        "TBRMSILO.def",       "TBRMBLAK.def",       "TBRMSPEC.def",
        "TBRMEXT0.def",       "TBRMEXT1.def",       "TBRMHOLY.def",
        "TBRMEXT3.def",       "TBRMEXT4.def",       "TBRMEXT5.def",
        "TBRMHRD1.def",       "TBRMHRD2.def",       "TBRMHRD3.def",
        "TBRMHRD4.def",       "TBRMDW_0.def",       "TBRMDW_1.def",
        "TBRMDW_2.def",       "TBRMDW_3.def",       "TBRMDW_4.def",
        "TBRMDW_5.def",       "TBRMDW_6.def",       "TBRMUP_0.def",
        "TBRMUP_1.def",       "TBRMUP_2.def",       "TBRMUP_3.def",
        "TBRMUP_4.def",       "TBRMUP_5.def",       "TBRMUP_6.def",
        "AH00_.def",          "AH01_.def",          "AH02_.def",
        "AH03_.def",          "AH04_.def",          "AH05_.def",
        "AH06_.def",          "AH07_.def",          "AH08_.def",
        "AH09_.def",          "AH10_.def",          "AH11_.def",
        "AH12_.def",          "AH13_.def",          "AH14_.def",
        "AH15_.def",          "AH16_.def",          "AH17_.def",
        "AF00.def",           "AF01.def",           "AF02.def",
        "AF03.def",           "AF04.def",           "AF05.def",
        "AF06.def",           "AF07.def",           "ABF01L.def",
        "ABF01G.def",         "ABF01R.def",         "ABF01D.def",
        "ABF01B.def",         "ABF01P.def",         "ABF01W.def",
        "ABF01K.def",         "ABF02L.def",         "ABF02G.def",
        "ABF02R.def",         "ABF02D.def",         "ABF02B.def",
        "ABF02P.def",         "ABF02W.def",         "ABF02K.def",
        "ABF03L.def",         "ABF03G.def",         "ABF03R.def",
        "ABF03D.def",         "ABF03B.def",         "ABF03P.def",
        "ABF03W.def",         "ABF03K.def",         "AVWmrnd0.def",
        "AVLholg0.def",       "AvTCave.def",        "AVXboat2.def",
        "AVWpikx0.def",       "AVTgems0.def",       "AVTore0.def",
        "AVA0014.def",        "AVA0011.def",        "AVA0008.def",
        "AVA0007.def",        "AvWMonk.def",        "AVXccht0.def",
        "AVLdead7.def",       "AVMwndd0.def",       "AVTcrys0.def",
        "AVTsulf0.def",       "AVTgold0.def",       "AVXboat0.def",
        "AVXboat1.def",       "AVTchst0.def",       "AVSuniv0.def",
        "AVA0128.def",        "AVXtvrn0.def",       "AVXtomb0.def",
        "AVXmktb0.def",       "AVMwwhl0.def",       "AVWpegx0.def",
        "agemLL.def",         "agemLR.def",         "agemUL.def",
        "agemUR.def",         "IMOBIL.def",         "IMANA.def",
        "ADVVIEW.DEF",        "ADVPUZ.DEF",         "ADVDIG.DEF",
        "ADVINFO.DEF",        "ADVTURN.DEF",        "IOK6432.DEF",
        "SYSOPB1.DEF",        "SYSOPB2.DEF",        "SYSOPB3.DEF",
        "SYSOPB4.DEF",        "SYSOPB5.DEF",        "SYSOPB6.DEF",
        "SYSOPB7.DEF",        "SYSOPB8.DEF",        "SYSOPB9.DEF",
        "SYSOB10.DEF",        "SYSOB11.DEF",        "SYSOB12.DEF",
        "SYSOB13.DEF",        "SYSOPCHK.DEF",       "SOLOAD.DEF",
        "SOSAVE.DEF",         "SORSTRT.DEF",        "SOMAIN.DEF",
        "soquit.DEF",         "soretrn.DEF",        "CRADVNTR.def",
        "ITPA.DEF",           "SpelTab.DEF",        "Spells.DEF",
        "SplevA.DEF",         "SplevF.DEF",         "SplevW.DEF",
        "SplevE.DEF",         "hsbtns3.def",        "hsbtns5.def",
        "UN32.def",           "UN44.def",           "ITMCLS.def",
        "ITMTLS.def",         "itpt.def",           "OVBUTN4.def",
        "IBY6432.DEF",        "ICANCEL.DEF",        "IRCBTNS.DEF",
        "IDV6432.DEF",        "PSKIL32.def",        "PSKIL32.def",
        "PSKIL42.def",        "PSKILL.def",         "SECSK32.def",
        "SECSK32.def",        "SECSKILL.def",       "SECSK82.def",
        "SMALRES.def",        "RESOURCE.def",       "RESOURCE.def",
        "RESOUR82.def",       "CPRSMALL.def",       "CPRSMALL.def",
        "CPRSMALL.def",       "TWCRPORT.def",       "Artifact.def",
        "Artifact.def",       "Artifact.def",       "Artifact.def",
        "SpellInt.def",       "SpellInt.def",       "SpellInt.def",
        "SPELLSCR.def",       "IMRL22.def",         "IMRL30.def",
        "IMRL42.def",         "imrl82.def",         "ILCK22.def",
        "ILCK30.def",         "ILCK42.def",         "ilck82.def",
        "PortraitsSmall.def", "PortraitsSmall.def", "PortraitsSmall.def",
        "PortraitsLarge.def", "CREST58.def",        "CREST58.def",
        "CREST58.def",        "CREST58.def",        "iOKAY.def",
        "IOKAY32.def",        "IOK6432.def",        "CREST58.def",
        "PSKIL42.def",        "hsbtns.DEF",         "hsbtns4.DEF",
        "hsbtns2.DEF",        "hsbtns6.DEF",        "hsbtns7.DEF",
        "hsbtns8.DEF",        "hsbtns9.DEF",        "tsbtns.def",
        "TPTAV01.DEF",        "TPTAV02.DEF"};
    for (const auto &filePath : filePaths) {
      Def def("./Data/H3sprite.lod/" + filePath);
      for (uint8_t j = 0; j < def.offset.size(); j++) {
        Global::defCache[filePath + "/" + std::to_string(j)] = def.loadGroup(j);
      }
    }
  };
  auto loadColor = []() {
    const std::vector<std::string> filePaths = {
        "AVCftrx0.def", "AVCstrx0.def", "AVMcrrf0.def", "AVMgorf0.def",
        "AVMgerf0.def", "AVMorro0.def", "AVMsawr0.def", "AVMsulf0.def",
        "AVMorsw0.def", "AVGelem0.def", "AVCnecx0.def", "AVCrand0.def",
        "AVGcavl0.def", "AVWmrnd0.def", "AVLholg0.def", "AvTCave.def",
        "AVCcasx0.def", "AVXboat2.def", "AVWpikx0.def", "AVTgems0.def",
        "AVTore0.def",  "AVA0014.def",  "AVA0011.def",  "AVA0008.def",
        "AVA0007.def",  "AvWMonk.def",  "AVXccht0.def", "AVLdead7.def",
        "AVMwndd0.def", "AVTcrys0.def", "AVTsulf0.def", "AVTgold0.def",
        "AVXboat0.def", "AVXboat1.def", "AVCramx0.def", "AVTchst0.def",
        "AVGcros0.def", "AVSuniv0.def", "AVA0128.def",  "AVXshyd0.def",
        "AVXtvrn0.def", "AVMalch0.def", "AVCgar10.def", "AVXtomb0.def",
        "AVXmktb0.def", "AVMwwhl0.def", "AVWpegx0.def",
    };
    for (const auto &filePath : filePaths) {
      for (int i = 0; i <= 8; i++) {
        Def def("./Data/H3sprite.lod/" + filePath);
        def.setColor(i);
        Global::defCache[filePath + "/0/" + std::to_string(i)] =
            def.loadGroup(0);
      }
    }
  };
  auto loadTerrain = []() {
    const std::vector<std::string> filePaths = {
        "DIRTTL.def", "SANDTL.def", "GRASTL.def", "SNOWTL.def", "SWMPTL.def",
        "ROUGTL.def", "SUBBTL.def", "LAVATL.def", "WATRTL.def", "ROCKTL.def",
        "clrrvr.def", "icyrvr.def", "mudrvr.def", "lavrvr.def", "dirtrd.def",
        "gravrd.def", "cobbrd.def", "adag.def",
    };

    const std::unordered_map<std::string,
                             std::vector<std::pair<uint8_t, uint8_t>>>
        fileAni = {
            {"LAVATL.def", {{246, 9}}},
            {"WATRTL.def", {{229, 12}, {242, 12}}},
            {"clrrvr.def", {{183, 12}, {195, 6}}},
            {"mudrvr.def", {{228, 12}, {183, 6}, {240, 6}}},
            {"lavrvr.def", {{240, 9}}},
        };
    for (const auto &filePath : filePaths) {
      Def def("./Data/H3sprite.lod/" + filePath);
      if (fileAni.contains(filePath)) {
        for (uint8_t i = 0; i < def.offset[0].size(); i++) {
          Global::defCache[filePath + "/" + std::to_string(i)] =
              def.loadPalette(fileAni.at(filePath), i);
        }
      } else {
        for (uint8_t i = 0; i < def.offset[0].size(); i++) {
          Global::defCache[filePath + "/" + std::to_string(i)] =
              std::vector<SDL_Texture *>{def.loadFrame(0, i)};
        }
      }
    }
  };
  const auto loadPal = []() {
    const std::vector<std::string> filePaths = {
        "DIALGBOX.def", "IAM002.DEF", "IAM010.DEF", "IAM003.DEF", "IAM004.DEF",
        "IAM005.DEF",   "IAM011.DEF", "IAM006.DEF", "IAM007.DEF", "IAM008.DEF",
        "IAM009.DEF",   "IAM000.DEF", "IAM001.DEF",
    };
    for (const auto &filePath : filePaths) {
      Def def("./Data/H3sprite.lod/" + filePath);
      for (int i = 0; i < 8; ++i) {
        memcpy(&def.palette[224], &PlayerPal::palette[i][0],
               32 * sizeof(SDL_Color));
        Global::defCache[filePath + "/" + std::to_string(i)] = def.loadGroup(0);
      }
    }
  };
  const auto loadFog = []() {
    auto fogOfWarFullHide = Def("./Data/H3sprite.lod/TSHRC.def").loadGroup(0);
    Global::defCache["TSHRC.def"] = fogOfWarFullHide;
    auto fogOfWarPartialHide =
        Def("./Data/H3sprite.lod/TSHRE.def").loadGroup(0);
    const uint8_t rotations[] = {22, 15, 2,  13, 12, 16, 28, 17, 20,
                                 19, 7,  24, 26, 25, 30, 32, 27};
    for (auto i : rotations) {
      auto texture =
          SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_UNKNOWN,
                            SDL_TEXTUREACCESS_TARGET, 32, 32);
      SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
      SDL_SetRenderTarget(Window::renderer, texture);
      SDL_RenderTextureRotated(Window::renderer, fogOfWarPartialHide[i],
                               nullptr, nullptr, 0, nullptr,
                               SDL_FLIP_HORIZONTAL);
      SDL_SetRenderTarget(Window::renderer, nullptr);
      fogOfWarPartialHide.push_back(texture);
    }
    Global::defCache["TSHRE.def"] = fogOfWarPartialHide;
  };
  const auto loadBoat = []() {
    const std::string boatFilePaths[] = {"AB01_.def", "AB02_.def", "AB03_.def"};
    const std::string waterFilePaths[] = {"ABM01_.def", "ABM02_.def",
                                          "ABM03_.def"};
    for (uint8_t i = 0; i < std::size(boatFilePaths); i++) {
      Def boatDef("./Data/H3sprite.lod/" + boatFilePaths[i]);
      Def waterDef("./Data/H3sprite.lod/" + waterFilePaths[i]);
      for (uint8_t j = 0; j < boatDef.offset.size(); j++) {
        auto boatTextures = boatDef.loadGroup(j);
        auto waterTextures = waterDef.loadGroup(j);
        std::vector<SDL_Texture *> targetTextures;
        SDL_FRect posRect{0, 0, 96, 64};
        for (uint8_t k = 0; k < boatTextures.size(); k++) {
          SDL_Texture *targetTexture =
              SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_UNKNOWN,
                                SDL_TEXTUREACCESS_TARGET, 96, 64);
          SDL_SetTextureBlendMode(targetTexture, SDL_BLENDMODE_BLEND);
          SDL_SetRenderTarget(Window::renderer, targetTexture);
          // 渲染第一个Texture
          SDL_RenderTexture(Window::renderer, waterTextures[k], NULL, &posRect);
          // 渲染第二个Texture
          SDL_RenderTexture(Window::renderer, boatTextures[k], NULL, &posRect);
          SDL_SetRenderTarget(Window::renderer, NULL);
          targetTextures.push_back(targetTexture);
        }
        for (auto vec : {boatTextures, waterTextures}) {
          for (auto texture : vec) {
            SDL_DestroyTexture(texture);
          }
        }
        Global::defCache[boatFilePaths[i] + "/" + std::to_string(j)] =
            targetTextures;
      }
    }
  };
  loadCommon();
  loadColor();
  loadTerrain();
  loadPal();
  loadFog();
  loadBoat();
}

void loadAudio() {
  const std::vector<std::string> filePaths = {
      "DANGER.wav",   "killfade.wav", "AITheme0.wav", "horse00.wav",
      "button.wav",   "CAVEHEAD.wav", "PICKUP01.wav", "PICKUP02.wav",
      "PICKUP03.wav", "PICKUP04.wav", "PICKUP05.wav", "PICKUP06.wav",
      "PICKUP07.wav"};
  for (auto filePath : filePaths) {
    SDL_AudioSpec spec;
    uint8_t *wav_data = NULL;
    uint32_t wav_data_len = 0;
    std::string wav_path = "Audio/" + filePath;
    SDL_LoadWAV(wav_path.c_str(), &spec, &wav_data, &wav_data_len);
    Global::pcmCache[filePath] =
        std::vector<uint8_t>(wav_data, wav_data + wav_data_len);
    SDL_free(wav_data);
  }
}

void Global::init() {
  loadDef();
  loadPcx();
  // loadAudio();
}

void Global::startGame() {
  const auto loadObelisk = []() {
    std::vector<ObeliskComp *> oVec;
    for (auto &r : World::registrys) {
      for (auto ent : r.view<ObeliskComp>()) {
        oVec.push_back(&r.get<ObeliskComp>(ent));
      }
    }
    auto total = PuzzleCfg::puzzleVec[0].size();
    auto obeSize = oVec.size();

    std::vector<std::vector<uint8_t>> distribution(obeSize);
    int base = total / obeSize;
    int remainder = total % obeSize;
    int current = 0;
    for (int i = 0; i < obeSize; ++i) {
      int num = base + (i < remainder ? 1 : 0);
      for (int j = 0; j < num; ++j) {
        distribution[i].push_back(current++);
      }
    }
    for (uint8_t i = 0; i < oVec.size(); i++) {
      oVec[i]->puzzles = distribution[i];
    }
  };
  const auto loadPuzzle = []() {
    std::unordered_set<int32_t> block;
    for (uint8_t i : {0, 1}) {
      auto &registry = World::registrys[i];
      for (auto ent : registry.view<GrailComp>()) {
        auto oComp = &registry.get<ObjectComp>(ent);
        Global::grailPair = {i, {oComp->x, oComp->y}};
      }
    }
    if (!Global::grailPair.has_value()) {
      auto &registry = World::registrys[0];
      for (auto ent : registry.view<ObjectComp>()) {
        auto objectComp = &registry.get<ObjectComp>(ent);
        if ((ObjectType)objectComp->type == ObjectType::MONSTER ||
            (ObjectType)objectComp->type == ObjectType::RESOURCE ||
            (ObjectType)objectComp->type == ObjectType::ARTIFACT ||
            (ObjectType)objectComp->type == ObjectType::CAMPFIRE ||
            (ObjectType)objectComp->type == ObjectType::HERO) {
          continue;
        }
        for (auto &vec : {objectComp->blockTiles, objectComp->accessTiles}) {
          for (auto i : vec) {
            auto x = objectComp->x + i.first;
            auto y = objectComp->y + i.second;
            block.insert(x + y * Global::mapSize);
          }
        }
      }
      std::unordered_set<int32_t> placePoint;
      placePoint.insert(landBlock[0].begin(), landBlock[0].end());
      placePoint.insert(coastalBlock[0].begin(), coastalBlock[0].end());
      std::vector<int32_t> placeVec(placePoint.begin(), placePoint.end());
      while (true) {
        std::uniform_int_distribution<size_t> dis(0, placeVec.size() - 1);
        auto r = placeVec[dis(Global::gen)];
        if (block.contains(r)) {
          continue;
        } else {
          Global::grailPair = {0, {r % Global::mapSize, r / Global::mapSize}};
          break;
        }
      }
    }
    SDL_Point grailPosition = Global::grailPair->second;
    grailPosition.x = grailPosition.x * 32;
    grailPosition.y = grailPosition.y * 32;
    auto grailOffsetL = grailPosition.x - 563;
    auto grailOffsetR = grailPosition.x;
    auto grailOffsetT = grailPosition.y - 514;
    auto grailOffsetB = grailPosition.y;
    if (grailOffsetL < 0) {
      grailOffsetL = 0;
    }
    if (grailOffsetR + 595 > Global::mapW) {
      grailOffsetR = Global::mapW - 595;
    }
    if (grailOffsetT < 0) {
      grailOffsetT = 0;
    }
    if (grailOffsetB + 546 > Global::mapH) {
      grailOffsetB = Global::mapH - 546;
    }
    std::uniform_int_distribution<size_t> disX(grailOffsetL, grailOffsetR);
    Global::puzzleOffset->x = disX(Global::gen);
    std::uniform_int_distribution<size_t> disY(grailOffsetT, grailOffsetB);
    Global::puzzleOffset->y = disY(Global::gen);
  };
  const auto loadTerMap = []() {
    for (uint8_t i = 0; i < 2; i++) {
      Global::puzzleMaps[i] =
          SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_UNKNOWN,
                            SDL_TEXTUREACCESS_TARGET, Global::mapW, mapH);
      SDL_SetTextureBlendMode(Global::puzzleMaps[i], SDL_BLENDMODE_BLEND);
      SDL_SetRenderTarget(Window::renderer, Global::puzzleMaps[i]);
      SDL_SetRenderDrawColor(Window::renderer, 0, 0, 0, 0);
      SDL_RenderClear(Window::renderer);

      auto &registry = World::registrys[i];
      for (auto ent : registry.view<TerrainComp>()) {
        auto tComp = &registry.get<TextureComp>(ent);
        auto pComp = &registry.get<PositionComp>(ent);
        auto texture = Global::defCache.at(tComp->path)[tComp->index];
        SDL_FRect posRect{(float)(int)pComp->point.x,
                          (float)(int)pComp->point.y, (float)texture->w,
                          (float)texture->h};
        SDL_RenderTextureRotated(Window::renderer, texture, nullptr, &posRect,
                                 0, nullptr, (SDL_FlipMode)pComp->flip);
      }
      for (auto ent : registry.view<ObjectComp>()) {
        auto oComp = &registry.get<ObjectComp>(ent);
        if ((ObjectType)oComp->type == ObjectType::MONSTER ||
            (ObjectType)oComp->type == ObjectType::RESOURCE) {
          auto tComp = &registry.get<TextureComp>(ent);
          auto pComp = &registry.get<PositionComp>(ent);
          auto texture = Global::defCache.at(tComp->path)[tComp->index];
          SDL_FRect posRect{(float)(int)pComp->point.x,
                            (float)(int)pComp->point.y, (float)texture->w,
                            (float)texture->h};
          SDL_RenderTextureRotated(Window::renderer, texture, nullptr, &posRect,
                                   0, nullptr, (SDL_FlipMode)pComp->flip);
        }
      }
      if (Global::grailPair->first == i) {
        auto texture = Global::defCache.at("adag.def/0")[0];
        auto point = Global::grailPair->second;
        SDL_FRect posRect{(float)(int)point.x * 32, (float)(int)point.y * 32,
                          (float)texture->w, (float)texture->h};
        SDL_RenderTexture(Window::renderer, texture, nullptr, &posRect);
      }
      SDL_Rect posRect = {0, 0, (int)(Global::mapW), (int)(Global::mapH)};
      auto surface = SDL_RenderReadPixels(Window::renderer, &posRect);
      if (surface && (surface->format != SDL_PIXELFORMAT_RGBA32)) {
        SDL_Surface *converted =
            SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
        SDL_DestroySurface(surface);
        surface = converted;
      }
      uint8_t *pixels = static_cast<uint8_t *>(surface->pixels);
      for (int yp = 0; yp < surface->h; ++yp) {
        uint8_t *pixelFrom = pixels + yp * surface->pitch;
        uint8_t *pixelDest = pixels + yp * surface->pitch + surface->w * 4;
        for (uint8_t *pixel = pixelFrom; pixel < pixelDest; pixel += 4) {
          // 假设RGBA8888格式：[R][G][B][A]
          uint8_t r = pixel[0];
          uint8_t g = pixel[1];
          uint8_t b = pixel[2];
          // 你的像素处理逻辑在这里
          // 例如灰度转换：
          uint8_t gray =
              static_cast<uint8_t>(0.299f * r + 0.587f * g + 0.114f * b);
          pixel[0] = gray; // R
          pixel[1] = gray; // G
          pixel[2] = gray; // B
        }
      }
      SDL_DestroyTexture(Global::puzzleMaps[i]);
      Global::puzzleMaps[i] =
          SDL_CreateTextureFromSurface(Window::renderer, surface);
      SDL_DestroySurface(surface); // 记得释放
    }
    SDL_SetRenderTarget(Window::renderer, nullptr);
  };

  const auto loadMiniMap = []() {
    for (uint8_t i = 0; i < 2; i++) {
      std::unordered_set<uint32_t> block;
      Global::miniMaps[i] = SDL_CreateTexture(
          Window::renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
          Global::mapSize, Global::mapSize);
      char *pixels = (char *)SDL_malloc(Global::mapSize * Global::mapSize * 4);
      auto &registry = World::registrys[i];
      for (auto ent : registry.view<ObjectComp>(entt::exclude<PlayerIdComp>)) {
        auto objectComp = &registry.get<ObjectComp>(ent);
        for (auto i : objectComp->blockTiles) {
          auto x = (objectComp->x + i.first) * 4;
          auto y = (objectComp->y + i.second) * Global::mapSize * 4;
          block.insert(y + x);
        }
      }
      for (auto ent : registry.view<TerrainComp>()) {
        auto terrainComp = &registry.get<TerrainComp>(ent);
        auto positionComp = &registry.get<PositionComp>(ent);
        SDL_Point positon{static_cast<int>(positionComp->point.x / 32),
                          static_cast<int>(positionComp->point.y / 32)};
        auto x = positon.x * 4;
        auto y = positon.y * Global::mapSize * 4;
        if (block.contains(y + x)) {
          auto color = TerrainCfg::minimapBlocked.at(terrainComp->index);
          pixels[y + x] = color.r;
          pixels[y + x + 1] = color.g;
          pixels[y + x + 2] = color.b;
          pixels[y + x + 3] = color.a;
        } else {
          auto color = TerrainCfg::minimapUnblocked.at(terrainComp->index);
          pixels[y + x] = color.r;
          pixels[y + x + 1] = color.g;
          pixels[y + x + 2] = color.b;
          pixels[y + x + 3] = color.a;
        }
      }
      SDL_UpdateTexture(Global::miniMaps[i], NULL, pixels, Global::mapSize * 4);
      SDL_free(pixels);
    }
  };
  const auto loadFogs = []() {
    for (uint8_t i = 0; i < 8; ++i) {
      for (uint8_t j = 0; j < 2; ++j) {
        Global::fogs[i][j].resize(Global::mapSize * Global::mapSize, false);
      }
    }
  };
  const auto loadHeroTowns = []() {
    Global::heroEnt = entt::null;
    Global::goalEnt = entt::null;

    Global::herosIndex.fill(0xff);
    Global::townsIndex.fill(0xffff);

    std::map<uint32_t, entt::entity> heroMap[2][8];
    for (auto i : {0, 1}) {
      auto registry = &World::registrys[i];
      for (auto ent : registry->view<HeroComp, ObjectComp, PlayerIdComp>()) {
        auto objectComp = registry->get<ObjectComp>(ent);
        auto playerIdComp = registry->get<PlayerIdComp>(ent);
        auto index = objectComp.x + objectComp.y * Global::mapSize;
        heroMap[i][playerIdComp.id][index] = ent;
        Global::heros[playerIdComp.id].push_back({i, ent});
      }
    }
    for (auto i : {0, 1}) {
      auto registry = &World::registrys[i];
      for (auto ent : registry->view<TownComp>()) {
        auto objectComp = registry->get<ObjectComp>(ent);
        auto playerIdComp = registry->get<PlayerIdComp>(ent);
        auto index = objectComp.x + objectComp.y * Global::mapSize;
        if (heroMap[i][playerIdComp.id].contains(index)) {
          auto heroEnt = heroMap[i][playerIdComp.id][index];
          registry->get<ObjectComp>(heroEnt).x -= 1;
          registry->get<PositionComp>(heroEnt).point.x -= 32;
          registry->get<PositionComp>(registry->get<HeroComp>(heroEnt).flagEnt)
              .point.x -= 32;
          registry->get<HeroComp>(heroEnt).curEnt = ent;
          registry->get<TownComp>(ent).heroEnt[1] = heroEnt;
        }
        if (playerIdComp.id < 8) {
          Global::towns[playerIdComp.id].push_back({i, ent});
        }
      }
    }
    World::needSort = true;
  };
  const auto loadGate = []() {
    std::vector<GateComp *> gateComps[2];
    std::vector<entt::entity> gateEnts[2];
    for (uint8_t i : {0, 1}) {
      auto &registry = World::registrys[i];
      registry.sort<GateComp>(
          [](const auto &l, const auto &r) { return l.order < r.order; });
      for (auto ent : registry.view<GateComp>()) {
        auto gateComp = &registry.get<GateComp>(ent);
        gateComps[i].push_back(gateComp);
        gateEnts[i].push_back(ent);
      }
    }
    for (uint16_t i = 0; i < gateComps[0].size(); i++) {
      if (i < gateComps[1].size()) {
        std::swap(gateComps[0][i]->x, gateComps[1][i]->x);
        std::swap(gateComps[0][i]->y, gateComps[1][i]->y);
        gateComps[0][i]->level = 1;
        gateComps[1][i]->level = 0;

        gateComps[0][i]->goalEnt = gateEnts[1][i];
        gateComps[1][i]->goalEnt = gateEnts[0][i];
      }
    }
  };
  const auto loadMonoTwoWay = []() {
    std::unordered_map<uint8_t, std::vector<entt::entity>> monoMap[2];
    for (uint8_t i : {0, 1}) {
      auto &registry = World::registrys[i];
      for (auto ent : registry.view<MonolithComp>()) {
        auto mComp = &registry.get<MonolithComp>(ent);
        if (mComp->twoWay == false) {
          continue;
        }
        auto &v = monoMap[i][mComp->id];
        v.push_back(ent);
      }
    }
    for (uint8_t i : {0, 1}) {
      auto &registry = World::registrys[i];
      auto mCps = monoMap[i];
      for (auto [k, v] : mCps) {
        for (auto ent : v) {
          auto mComp = &registry.get<MonolithComp>(ent);
          auto v2 = v;
          std::erase(v2, ent);
          mComp->goalEnt = v2;
        }
      }
    }
  };
  const auto loadMonoOneWay = []() {
    std::unordered_map<uint8_t, std::vector<entt::entity>> monoMap[2];
    for (uint8_t i : {0, 1}) {
      auto &registry = World::registrys[i];
      for (auto ent : registry.view<MonolithComp>()) {
        auto mComp = &registry.get<MonolithComp>(ent);
        if (mComp->twoWay == true || mComp->entrance == true) {
          continue;
        }
        auto &v = monoMap[i][mComp->id];
        v.push_back(ent);
      }
    }
    for (uint8_t i : {0, 1}) {
      auto &registry = World::registrys[i];
      auto mCps = monoMap[i];
      for (auto ent : registry.view<MonolithComp>()) {
        auto mComp = &registry.get<MonolithComp>(ent);
        if (mComp->twoWay == false && mComp->entrance == true) {
          mComp->goalEnt = mCps[mComp->id];
        }
      }
    }
  };
  const auto loadWhirlpool = []() {
    std::vector<entt::entity> wVec[2];
    for (uint8_t i : {0, 1}) {
      auto &registry = World::registrys[i];
      for (auto ent : registry.view<WhirlpoolComp>()) {
        wVec[i].push_back(ent);
      }
    }
    for (uint8_t i : {0, 1}) {
      auto &registry = World::registrys[i];
      for (auto ent : registry.view<WhirlpoolComp>()) {
        auto wComp = &registry.get<WhirlpoolComp>(ent);
        auto v = wVec[i];
        std::erase(v, ent);
        wComp->goalEnt = v;
      }
    }
  };
  const auto loadHeroLevel = []() {
    for (uint8_t i : {0, 1}) {
      auto &registry = World::registrys[i];
      for (auto ent : registry.view<HeroComp>()) {
        auto hComp = &registry.get<HeroComp>(ent);
        for (uint8_t i = 1; i < std::size(HeroCfg::heroLevelExp); i++) {
          if (hComp->exp >= HeroCfg::heroLevelExp[i]) {
            hComp->level = i + 1;
            LevelUpSys::prepareLvlUp(*hComp);
            hComp->primSkills[Global::lvlPrimIndex] += 1;
            if (Global::lvlSecPair.first != 0xff) {
              LevelUpSys::studySecSki(*hComp, Global::lvlSecPair.first);
            }
          }
        }
      }
    }
  };
  const auto loadTavernHero = []() {
    int arr[101];
    for (int i = 0; i <= 100; ++i) {
      arr[i] = i;
    }
    std::set<int> numbers(arr, arr + 101);
    for (auto m : {0, 1}) {
      auto &registry = World::registrys[m];
      for (auto ent : registry.view<HeroComp>()) {
        auto hComp = registry.get<HeroComp>(ent);
        numbers.erase(hComp.portrait);
      }
    }
    for (auto n : {0, 1}) {
      if (numbers.size() > 0) {
        int random = rand() % numbers.size();
        auto it = std::next(numbers.begin(), random);

        auto heroEnt = World::registrys[0].create();
        auto &hComp = World::registrys[0].emplace<HeroComp>(heroEnt);
        hComp.portrait = *it;
        auto secSkills = HeroCfg::heroSecSkills.at(hComp.portrait);
        hComp.secSkills = secSkills;
        hComp.level = 1;
        hComp.primSkills = HeroCfg::heroPrimarySkills.at(0);

        for (auto pair : HeroCfg::heroCreatures[hComp.portrait]) {
          switch (pair.first) {
          case (uint16_t)CreatureCfg::Creature::CATAPULT:
          case (uint16_t)CreatureCfg::Creature::BALLISTA:
          case (uint16_t)CreatureCfg::Creature::FIRST_AID_TENT:
          case (uint16_t)CreatureCfg::Creature::AMMO_CART: {
            break;
          }
          default: {
            hComp.creatures.push_back(pair);
            break;
          }
          }
        }

        numbers.erase(it);
        Global::tavernHeros[Global::playerId][n] = heroEnt;
      }
    }
  };
  // loadObelisk();
  // loadPuzzle();
  // loadTerMap();
  loadMiniMap();
  loadFogs();
  loadHeroTowns();
  loadGate();
  loadMonoTwoWay();
  loadMonoOneWay();
  loadWhirlpool();
  loadHeroLevel();
  loadTavernHero();
}

void Global::endGame() {
  Global::playerAlliance.clear();

  Global::resources = {};
  Global::terrains = {};
  Global::landBlock = {};
  Global::waterBlock = {};
  Global::rockBlock = {};
  Global::coastalBlock = {};
  Global::fogs = {};
  Global::heros = {};
  Global::towns = {};

  for (auto &m : Global::miniMaps) {
    SDL_DestroyTexture(m);
  }
  for (auto &p : Global::puzzleMaps) {
    SDL_DestroyTexture(p);
  }

  for (auto &r : World::registrys) {
    r = {};
  }

  Global::herosIndex.fill(0xff);
  Global::townsIndex.fill(0xffff);

  Global::heroMove = false;
}