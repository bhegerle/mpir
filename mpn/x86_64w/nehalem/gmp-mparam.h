/* Generated by tuneup.c, 2011-11-22, gcc 4.4 */

#define MUL_KARATSUBA_THRESHOLD          16
#define MUL_TOOM3_THRESHOLD              90
#define MUL_TOOM4_THRESHOLD             166
#define MUL_TOOM8H_THRESHOLD            270

#define SQR_BASECASE_THRESHOLD            0  /* always (native) */
#define SQR_KARATSUBA_THRESHOLD          31
#define SQR_TOOM3_THRESHOLD              89
#define SQR_TOOM4_THRESHOLD             248
#define SQR_TOOM8_THRESHOLD             321

#define POWM_THRESHOLD                  107

#define HGCD_THRESHOLD                  178
#define GCD_DC_THRESHOLD               2464
#define GCDEXT_DC_THRESHOLD            1788
#define JACOBI_BASE_METHOD                1

#define DIVREM_1_NORM_THRESHOLD       MP_SIZE_T_MAX  /* never */
#define DIVREM_1_UNNORM_THRESHOLD     MP_SIZE_T_MAX  /* never */
#define MOD_1_NORM_THRESHOLD              0  /* always */
#define MOD_1_UNNORM_THRESHOLD            0  /* always */
#define USE_PREINV_DIVREM_1               1  /* native */
#define USE_PREINV_MOD_1                  1
#define DIVEXACT_1_THRESHOLD              0  /* always */
#define MODEXACT_1_ODD_THRESHOLD          0  /* always (native) */
#define MOD_1_1_THRESHOLD                 5
#define MOD_1_2_THRESHOLD                 8
#define MOD_1_3_THRESHOLD                17
#define DIVREM_HENSEL_QR_1_THRESHOLD     14
#define RSH_DIVREM_HENSEL_QR_1_THRESHOLD      7
#define DIVREM_EUCLID_HENSEL_THRESHOLD    108

#define ROOTREM_THRESHOLD                 6

#define GET_STR_DC_THRESHOLD             15
#define GET_STR_PRECOMPUTE_THRESHOLD     21
#define SET_STR_DC_THRESHOLD           6390
#define SET_STR_PRECOMPUTE_THRESHOLD   6517

#define MUL_FFT_TABLE  { 336, 736, 1856, 2304, 7168, 20480, 81920, 327680, 1310720, 5242880, 0 }
#define MUL_FFT_MODF_THRESHOLD          336
#define MUL_FFT_FULL_THRESHOLD         1984

#define SQR_FFT_TABLE  { 304, 672, 1728, 2304, 7168, 28672, 81920, 327680, 1310720, 5242880, 0 }
#define SQR_FFT_MODF_THRESHOLD          304
#define SQR_FFT_FULL_THRESHOLD         1856

#define MULLOW_BASECASE_THRESHOLD         7
#define MULLOW_DC_THRESHOLD              11
#define MULLOW_MUL_THRESHOLD           3207

#define MULHIGH_BASECASE_THRESHOLD       17
#define MULHIGH_DC_THRESHOLD             17
#define MULHIGH_MUL_THRESHOLD          3207

#define MULMOD_2EXPM1_THRESHOLD          14

#define FAC_UI_THRESHOLD              12884
#define DC_DIV_QR_THRESHOLD              36
#define DC_DIVAPPR_Q_N_THRESHOLD         57
#define INV_DIV_QR_THRESHOLD           2492
#define INV_DIVAPPR_Q_N_THRESHOLD        57
#define DC_DIV_Q_THRESHOLD               97
#define INV_DIV_Q_THRESHOLD            3547
#define DC_DIVAPPR_Q_THRESHOLD           73
#define INV_DIVAPPR_Q_THRESHOLD        7350
#define DC_BDIV_QR_THRESHOLD             36
#define DC_BDIV_Q_THRESHOLD              11
/* Tuneup completed successfully, took 351 seconds */


#define MUL_FFT_TABLE2 {{1, 4}, {278, 5}, {292, 4}, {306, 5}, {328, 4}, {344, 5}, {360, 4}, {377, 5}, {386, 4}, {395, 5}, {680, 6}, {711, 5}, {743, 6}, {760, 4}, {777, 5}, {795, 6}, {1760, 7}, {1799, 6}, {1839, 7}, {1922, 6}, {2009, 7}, {2610, 8}, {2668, 7}, {2727, 8}, {2849, 7}, {3109, 8}, {3393, 7}, {3468, 8}, {5478, 9}, {5721, 8}, {6518, 9}, {6661, 8}, {6957, 9}, {7756, 8}, {8460, 9}, {8836, 8}, {9030, 9}, {9850, 8}, {10066, 9}, {10287, 10}, {10513, 9}, {10744, 10}, {10980, 9}, {11221, 10}, {11467, 9}, {13939, 10}, {15535, 9}, {18084, 10}, {19722, 9}, {20154, 10}, {23970, 9}, {24495, 10}, {27898, 11}, {31091, 10}, {31772, 9}, {32468, 10}, {40326, 11}, {47962, 10}, {52305, 11}, {53451, 12}, {63570, 10}, {73983, 11}, {80681, 10}, {82448, 11}, {114110, 12}, {127165, 11}, {164920, 12}, {196129, 13}, {254354, 12}, {259924, 11}, {277377, 12}, {392279, 13}, {519871, 12}, {531255, 11}, {659749, 12}, {674196, 13}, {784582, 12}, {995682, 13}, {MP_SIZE_T_MAX,0}}

#define MUL_FFTM_TABLE2 {{1, 4}, {254, 5}, {260, 6}, {266, 4}, {278, 5}, {292, 4}, {306, 5}, {360, 4}, {368, 5}, {622, 6}, {650, 5}, {680, 6}, {727, 5}, {743, 6}, {1352, 7}, {1413, 6}, {1476, 7}, {3248, 8}, {3393, 7}, {3468, 8}, {3622, 7}, {3784, 8}, {3867, 7}, {4039, 8}, {5478, 9}, {5721, 8}, {6241, 9}, {6661, 8}, {6957, 9}, {7756, 8}, {8100, 9}, {10980, 10}, {11467, 9}, {13061, 10}, {13347, 9}, {13939, 10}, {15535, 9}, {15876, 10}, {16580, 9}, {16944, 10}, {19722, 9}, {20154, 10}, {27898, 11}, {31091, 10}, {36184, 11}, {39461, 10}, {40326, 11}, {47962, 10}, {49013, 11}, {55819, 12}, {58292, 13}, {62207, 12}, {63570, 10}, {64963, 11}, {80681, 12}, {95949, 11}, {114110, 12}, {116609, 13}, {124440, 12}, {127165, 11}, {138676, 12}, {161386, 11}, {164920, 12}, {228243, 13}, {254354, 12}, {329862, 13}, {392279, 14}, {508731, 13}, {519871, 12}, {554776, 11}, {566925, 12}, {579340, 13}, {784582, 14}, {MP_SIZE_T_MAX,0}}

#define SQR_FFT_TABLE2 {{1, 4}, {278, 5}, {292, 4}, {306, 5}, {622, 6}, {650, 5}, {680, 6}, {711, 5}, {743, 6}, {1612, 7}, {1685, 6}, {1760, 7}, {1799, 6}, {1880, 7}, {1922, 6}, {2009, 7}, {2610, 8}, {2849, 7}, {2976, 8}, {5478, 9}, {5721, 8}, {6518, 9}, {6661, 8}, {6957, 9}, {7756, 8}, {8100, 9}, {8278, 8}, {8460, 9}, {8836, 8}, {9030, 9}, {9850, 8}, {10066, 9}, {13939, 10}, {15535, 9}, {18084, 10}, {19722, 9}, {20154, 10}, {23970, 9}, {24495, 10}, {27898, 11}, {31091, 10}, {31772, 9}, {32468, 10}, {40326, 11}, {47962, 10}, {52305, 11}, {53451, 12}, {63570, 10}, {69326, 11}, {98051, 12}, {127165, 11}, {164920, 12}, {196129, 13}, {254354, 12}, {259924, 11}, {265616, 10}, {296001, 11}, {302483, 12}, {329862, 11}, {344468, 12}, {392279, 13}, {519871, 12}, {531255, 11}, {631776, 12}, {659749, 11}, {688959, 12}, {704046, 13}, {784582, 14}, {801763, 12}, {995682, 13}, {MP_SIZE_T_MAX,0}}

#define SQR_FFTM_TABLE2 {{1, 4}, {242, 5}, {260, 4}, {278, 5}, {555, 6}, {581, 5}, {622, 6}, {711, 5}, {743, 6}, {1238, 7}, {1294, 6}, {1352, 7}, {1413, 6}, {1476, 7}, {2976, 8}, {3109, 7}, {3248, 8}, {3393, 7}, {3468, 8}, {3622, 7}, {3784, 8}, {5478, 9}, {5721, 8}, {5976, 9}, {6661, 8}, {6957, 9}, {10980, 10}, {11467, 9}, {13061, 10}, {13347, 9}, {13939, 10}, {15535, 9}, {15876, 10}, {16580, 9}, {16944, 10}, {17696, 9}, {18084, 10}, {19722, 9}, {20154, 10}, {27898, 11}, {31091, 10}, {36184, 11}, {39461, 10}, {40326, 11}, {47962, 10}, {49013, 11}, {55819, 12}, {58292, 13}, {62207, 12}, {63570, 10}, {64963, 11}, {80681, 12}, {95949, 11}, {104637, 12}, {127165, 11}, {138676, 12}, {161386, 11}, {164920, 12}, {196129, 13}, {254354, 12}, {329862, 13}, {392279, 14}, {508731, 13}, {519871, 12}, {531255, 11}, {592026, 12}, {604990, 13}, {659749, 12}, {688959, 13}, {784582, 14}, {MP_SIZE_T_MAX,0}}

#define MUL_FFT_FULL_TABLE2 {{16, 2}, {1022, 1}, {1045, 2}, {1068, 1}, {1092, 2}, {1116, 1}, {1422, 2}, {1454, 1}, {1553, 2}, {1623, 1}, {1696, 2}, {1734, 4}, {1772, 1}, {1811, 2}, {1851, 1}, {1934, 2}, {1977, 4}, {2021, 1}, {2066, 4}, {2112, 6}, {2306, 5}, {2357, 4}, {2409, 1}, {2462, 2}, {2516, 3}, {2572, 4}, {2746, 2}, {2932, 4}, {3063, 3}, {3131, 6}, {3200, 2}, {3271, 1}, {3343, 4}, {3417, 2}, {3648, 4}, {3728, 1}, {3894, 2}, {4068, 1}, {4158, 2}, {4250, 1}, {4440, 4}, {4538, 5}, {4638, 4}, {4844, 1}, {4951, 3}, {5171, 2}, {5285, 1}, {5401, 4}, {5520, 1}, {5641, 2}, {5765, 1}, {5892, 4}, {6154, 1}, {6427, 2}, {6568, 1}, {6712, 4}, {6859, 1}, {7010, 4}, {7164, 2}, {7321, 4}, {7482, 1}, {7986, 2}, {8161, 1}, {8340, 2}, {8523, 1}, {8710, 2}, {8901, 5}, {9296, 1}, {9922, 3}, {10363, 2}, {10590, 1}, {10822, 2}, {11550, 1}, {11803, 2}, {12062, 4}, {12327, 1}, {14040, 4}, {14348, 2}, {14663, 4}, {14985, 1}, {15993, 2}, {17068, 4}, {17442, 2}, {17824, 5}, {19022, 4}, {19439, 1}, {19865, 3}, {20745, 1}, {21665, 2}, {23121, 1}, {23628, 2}, {24146, 4}, {24675, 1}, {28104, 4}, {29992, 1}, {32007, 2}, {35670, 5}, {37251, 4}, {38067, 5}, {38901, 1}, {40624, 3}, {41514, 1}, {42424, 2}, {46266, 1}, {47280, 4}, {50456, 3}, {53845, 5}, {56230, 1}, {58721, 4}, {60007, 3}, {62664, 6}, {65440, 8}, {66873, 10}, {68338, 9}, {69835, 7}, {71365, 8}, {72928, 5}, {74525, 4}, {79530, 1}, {81272, 3}, {83052, 1}, {84871, 3}, {86730, 2}, {88630, 1}, {94582, 4}, {96654, 2}, {98771, 4}, {100934, 1}, {105404, 2}, {107713, 1}, {130905, 2}, {142755, 5}, {149076, 6}, {152341, 3}, {159086, 4}, {162570, 3}, {166130, 2}, {169768, 3}, {173486, 2}, {185136, 1}, {189190, 2}, {197567, 4}, {201894, 3}, {206315, 1}, {261830, 2}, {267564, 5}, {273423, 7}, {279411, 9}, {291783, 7}, {298173, 6}, {304703, 4}, {325163, 3}, {346997, 2}, {395159, 4}, {403812, 1}, {523686, 2}, {583592, 4}, {596372, 3}, {609431, 1}, {650350, 2}, {664591, 3}, {694016, 2}, {724743, 1}, {790340, 4}, {825333, 1}, {MP_SIZE_T_MAX,0}}

#define SQR_FFT_FULL_TABLE2 {{16, 1}, {1092, 2}, {1116, 1}, {1219, 2}, {1274, 1}, {1422, 2}, {1454, 1}, {1553, 2}, {1659, 1}, {1696, 4}, {1772, 1}, {1811, 2}, {1851, 1}, {1934, 4}, {2021, 1}, {2066, 4}, {2112, 6}, {2256, 5}, {2357, 4}, {2409, 3}, {2462, 2}, {2516, 3}, {2572, 4}, {2746, 2}, {2932, 4}, {3063, 2}, {3271, 1}, {3343, 4}, {3417, 2}, {3492, 4}, {3569, 3}, {3648, 4}, {3728, 1}, {3894, 2}, {4068, 1}, {4158, 2}, {4250, 1}, {4440, 4}, {4538, 5}, {4638, 4}, {4844, 1}, {4951, 3}, {5171, 2}, {5285, 1}, {5401, 4}, {5520, 1}, {5641, 2}, {5765, 1}, {5892, 4}, {6154, 6}, {6289, 2}, {6568, 1}, {6712, 4}, {6859, 1}, {7010, 4}, {7164, 2}, {7321, 1}, {7814, 2}, {8161, 1}, {8340, 2}, {8523, 1}, {8710, 2}, {8901, 5}, {9296, 1}, {9500, 4}, {9709, 1}, {9922, 3}, {10363, 2}, {10590, 1}, {10822, 2}, {11550, 1}, {11803, 4}, {12327, 1}, {12873, 2}, {13155, 1}, {14040, 4}, {14348, 1}, {15993, 2}, {17068, 4}, {17442, 2}, {17824, 5}, {19022, 4}, {19439, 1}, {19865, 3}, {20745, 1}, {21200, 2}, {23121, 1}, {23628, 2}, {24146, 4}, {24675, 1}, {32007, 2}, {35670, 1}, {36452, 4}, {38901, 1}, {40624, 3}, {41514, 2}, {46266, 1}, {47280, 4}, {50456, 3}, {53845, 1}, {58721, 4}, {60007, 3}, {62664, 6}, {64037, 8}, {65440, 10}, {66873, 13}, {68338, 9}, {69835, 6}, {71365, 8}, {72928, 5}, {74525, 4}, {79530, 1}, {81272, 3}, {83052, 2}, {88630, 1}, {94582, 4}, {96654, 2}, {98771, 1}, {130905, 2}, {142755, 5}, {149076, 6}, {152341, 3}, {166130, 2}, {197567, 4}, {201894, 1}, {261830, 2}, {267564, 5}, {273423, 7}, {279411, 9}, {291783, 7}, {298173, 6}, {304703, 4}, {325163, 3}, {346997, 2}, {395159, 4}, {403812, 1}, {523686, 2}, {583592, 4}, {596372, 6}, {609431, 5}, {622776, 4}, {636414, 1}, {650350, 2}, {664591, 3}, {694016, 2}, {790340, 4}, {825333, 1}, {843406, 3}, {861875, 1}, {MP_SIZE_T_MAX,0}}

