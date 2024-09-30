#include "math_util.h"

#include "global.h"

extern const s16 FX_SinCosTable_[]; // temporary until further notice

/*
 * Constant tables
 */
const fx32 gSineTable[] = {
    FX32_CONST(0.0),             // sin(0)
    FX32_CONST(0.017333984375),  // sin(1)
    FX32_CONST(0.034912109375),  // sin(2)
    FX32_CONST(0.05224609375),   // sin(3)
    FX32_CONST(0.06982421875),   // sin(4)
    FX32_CONST(0.087158203125),  // sin(5)
    FX32_CONST(0.1044921875),    // sin(6)
    FX32_CONST(0.121826171875),  // sin(7)
    FX32_CONST(0.13916015625),   // sin(8)
    FX32_CONST(0.156494140625),  // sin(9)
    FX32_CONST(0.173583984375),  // sin(10)
    FX32_CONST(0.19091796875),   // sin(11)
    FX32_CONST(0.2080078125),    // sin(12)
    FX32_CONST(0.224853515625),  // sin(13)
    FX32_CONST(0.241943359375),  // sin(14)
    FX32_CONST(0.2587890625),    // sin(15)
    FX32_CONST(0.275634765625),  // sin(16)
    FX32_CONST(0.29248046875),   // sin(17)
    FX32_CONST(0.30908203125),   // sin(18)
    FX32_CONST(0.32568359375),   // sin(19)
    FX32_CONST(0.342041015625),  // sin(20)
    FX32_CONST(0.3583984375),    // sin(21)
    FX32_CONST(0.37451171875),   // sin(22)
    FX32_CONST(0.390625),        // sin(23)
    FX32_CONST(0.40673828125),   // sin(24)
    FX32_CONST(0.422607421875),  // sin(25)
    FX32_CONST(0.4384765625),    // sin(26)
    FX32_CONST(0.4541015625),    // sin(27)
    FX32_CONST(0.469482421875),  // sin(28)
    FX32_CONST(0.48486328125),   // sin(29)
    FX32_CONST(0.5),             // sin(30)
    FX32_CONST(0.51513671875),   // sin(31)
    FX32_CONST(0.530029296875),  // sin(32)
    FX32_CONST(0.544677734375),  // sin(33)
    FX32_CONST(0.55908203125),   // sin(34)
    FX32_CONST(0.573486328125),  // sin(35)
    FX32_CONST(0.587890625),     // sin(36)
    FX32_CONST(0.601806640625),  // sin(37)
    FX32_CONST(0.61572265625),   // sin(38)
    FX32_CONST(0.62939453125),   // sin(39)
    FX32_CONST(0.642822265625),  // sin(40)
    FX32_CONST(0.656005859375),  // sin(41)
    FX32_CONST(0.669189453125),  // sin(42)
    FX32_CONST(0.681884765625),  // sin(43)
    FX32_CONST(0.694580078125),  // sin(44)
    FX32_CONST(0.70703125),      // sin(45)
    FX32_CONST(0.71923828125),   // sin(46)
    FX32_CONST(0.7314453125),    // sin(47)
    FX32_CONST(0.7431640625),    // sin(48)
    FX32_CONST(0.754638671875),  // sin(49)
    FX32_CONST(0.76611328125),   // sin(50)
    FX32_CONST(0.777099609375),  // sin(51)
    FX32_CONST(0.7880859375),    // sin(52)
    FX32_CONST(0.798583984375),  // sin(53)
    FX32_CONST(0.80908203125),   // sin(54)
    FX32_CONST(0.819091796875),  // sin(55)
    FX32_CONST(0.8291015625),    // sin(56)
    FX32_CONST(0.838623046875),  // sin(57)
    FX32_CONST(0.84814453125),   // sin(58)
    FX32_CONST(0.857177734375),  // sin(59)
    FX32_CONST(0.865966796875),  // sin(60)
    FX32_CONST(0.87451171875),   // sin(61)
    FX32_CONST(0.883056640625),  // sin(62)
    FX32_CONST(0.89111328125),   // sin(63)
    FX32_CONST(0.898681640625),  // sin(64)
    FX32_CONST(0.90625),         // sin(65)
    FX32_CONST(0.91357421875),   // sin(66)
    FX32_CONST(0.92041015625),   // sin(67)
    FX32_CONST(0.92724609375),   // sin(68)
    FX32_CONST(0.93359375),      // sin(69)
    FX32_CONST(0.939697265625),  // sin(70)
    FX32_CONST(0.945556640625),  // sin(71)
    FX32_CONST(0.951171875),     // sin(72)
    FX32_CONST(0.956298828125),  // sin(73)
    FX32_CONST(0.961181640625),  // sin(74)
    FX32_CONST(0.9658203125),    // sin(75)
    FX32_CONST(0.97021484375),   // sin(76)
    FX32_CONST(0.974365234375),  // sin(77)
    FX32_CONST(0.97802734375),   // sin(78)
    FX32_CONST(0.981689453125),  // sin(79)
    FX32_CONST(0.98486328125),   // sin(80)
    FX32_CONST(0.98779296875),   // sin(81)
    FX32_CONST(0.990234375),     // sin(82)
    FX32_CONST(0.992431640625),  // sin(83)
    FX32_CONST(0.99462890625),   // sin(84)
    FX32_CONST(0.99609375),      // sin(85)
    FX32_CONST(0.99755859375),   // sin(86)
    FX32_CONST(0.99853515625),   // sin(87)
    FX32_CONST(0.99951171875),   // sin(88)
    FX32_CONST(0.999755859375),  // sin(89)
    FX32_CONST(1.0),             // sin(90)
    FX32_CONST(0.999755859375),  // sin(91)
    FX32_CONST(0.99951171875),   // sin(92)
    FX32_CONST(0.99853515625),   // sin(93)
    FX32_CONST(0.99755859375),   // sin(94)
    FX32_CONST(0.99609375),      // sin(95)
    FX32_CONST(0.99462890625),   // sin(96)
    FX32_CONST(0.992431640625),  // sin(97)
    FX32_CONST(0.990234375),     // sin(98)
    FX32_CONST(0.98779296875),   // sin(99)
    FX32_CONST(0.98486328125),   // sin(100)
    FX32_CONST(0.981689453125),  // sin(101)
    FX32_CONST(0.97802734375),   // sin(102)
    FX32_CONST(0.974365234375),  // sin(103)
    FX32_CONST(0.97021484375),   // sin(104)
    FX32_CONST(0.9658203125),    // sin(105)
    FX32_CONST(0.961181640625),  // sin(106)
    FX32_CONST(0.956298828125),  // sin(107)
    FX32_CONST(0.951171875),     // sin(108)
    FX32_CONST(0.945556640625),  // sin(109)
    FX32_CONST(0.939697265625),  // sin(110)
    FX32_CONST(0.93359375),      // sin(111)
    FX32_CONST(0.92724609375),   // sin(112)
    FX32_CONST(0.92041015625),   // sin(113)
    FX32_CONST(0.91357421875),   // sin(114)
    FX32_CONST(0.90625),         // sin(115)
    FX32_CONST(0.898681640625),  // sin(116)
    FX32_CONST(0.89111328125),   // sin(117)
    FX32_CONST(0.883056640625),  // sin(118)
    FX32_CONST(0.87451171875),   // sin(119)
    FX32_CONST(0.865966796875),  // sin(120)
    FX32_CONST(0.857177734375),  // sin(121)
    FX32_CONST(0.84814453125),   // sin(122)
    FX32_CONST(0.838623046875),  // sin(123)
    FX32_CONST(0.8291015625),    // sin(124)
    FX32_CONST(0.819091796875),  // sin(125)
    FX32_CONST(0.80908203125),   // sin(126)
    FX32_CONST(0.798583984375),  // sin(127)
    FX32_CONST(0.7880859375),    // sin(128)
    FX32_CONST(0.777099609375),  // sin(129)
    FX32_CONST(0.76611328125),   // sin(130)
    FX32_CONST(0.754638671875),  // sin(131)
    FX32_CONST(0.7431640625),    // sin(132)
    FX32_CONST(0.7314453125),    // sin(133)
    FX32_CONST(0.71923828125),   // sin(134)
    FX32_CONST(0.70703125),      // sin(135)
    FX32_CONST(0.694580078125),  // sin(136)
    FX32_CONST(0.681884765625),  // sin(137)
    FX32_CONST(0.669189453125),  // sin(138)
    FX32_CONST(0.656005859375),  // sin(139)
    FX32_CONST(0.642822265625),  // sin(140)
    FX32_CONST(0.62939453125),   // sin(141)
    FX32_CONST(0.61572265625),   // sin(142)
    FX32_CONST(0.601806640625),  // sin(143)
    FX32_CONST(0.587890625),     // sin(144)
    FX32_CONST(0.573486328125),  // sin(145)
    FX32_CONST(0.55908203125),   // sin(146)
    FX32_CONST(0.544677734375),  // sin(147)
    FX32_CONST(0.530029296875),  // sin(148)
    FX32_CONST(0.51513671875),   // sin(149)
    FX32_CONST(0.5),             // sin(150)
    FX32_CONST(0.48486328125),   // sin(151)
    FX32_CONST(0.469482421875),  // sin(152)
    FX32_CONST(0.4541015625),    // sin(153)
    FX32_CONST(0.4384765625),    // sin(154)
    FX32_CONST(0.422607421875),  // sin(155)
    FX32_CONST(0.40673828125),   // sin(156)
    FX32_CONST(0.390625),        // sin(157)
    FX32_CONST(0.37451171875),   // sin(158)
    FX32_CONST(0.3583984375),    // sin(159)
    FX32_CONST(0.342041015625),  // sin(160)
    FX32_CONST(0.32568359375),   // sin(161)
    FX32_CONST(0.30908203125),   // sin(162)
    FX32_CONST(0.29248046875),   // sin(163)
    FX32_CONST(0.275634765625),  // sin(164)
    FX32_CONST(0.2587890625),    // sin(165)
    FX32_CONST(0.241943359375),  // sin(166)
    FX32_CONST(0.224853515625),  // sin(167)
    FX32_CONST(0.2080078125),    // sin(168)
    FX32_CONST(0.19091796875),   // sin(169)
    FX32_CONST(0.173583984375),  // sin(170)
    FX32_CONST(0.156494140625),  // sin(171)
    FX32_CONST(0.13916015625),   // sin(172)
    FX32_CONST(0.121826171875),  // sin(173)
    FX32_CONST(0.1044921875),    // sin(174)
    FX32_CONST(0.087158203125),  // sin(175)
    FX32_CONST(0.06982421875),   // sin(176)
    FX32_CONST(0.05224609375),   // sin(177)
    FX32_CONST(0.034912109375),  // sin(178)
    FX32_CONST(0.017333984375),  // sin(179)
    FX32_CONST(0.0),             // sin(180)
    FX32_CONST(-0.017333984375), // sin(181)
    FX32_CONST(-0.034912109375), // sin(182)
    FX32_CONST(-0.05224609375),  // sin(183)
    FX32_CONST(-0.06982421875),  // sin(184)
    FX32_CONST(-0.087158203125), // sin(185)
    FX32_CONST(-0.1044921875),   // sin(186)
    FX32_CONST(-0.121826171875), // sin(187)
    FX32_CONST(-0.13916015625),  // sin(188)
    FX32_CONST(-0.156494140625), // sin(189)
    FX32_CONST(-0.173583984375), // sin(190)
    FX32_CONST(-0.19091796875),  // sin(191)
    FX32_CONST(-0.2080078125),   // sin(192)
    FX32_CONST(-0.224853515625), // sin(193)
    FX32_CONST(-0.241943359375), // sin(194)
    FX32_CONST(-0.2587890625),   // sin(195)
    FX32_CONST(-0.275634765625), // sin(196)
    FX32_CONST(-0.29248046875),  // sin(197)
    FX32_CONST(-0.30908203125),  // sin(198)
    FX32_CONST(-0.32568359375),  // sin(199)
    FX32_CONST(-0.342041015625), // sin(200)
    FX32_CONST(-0.3583984375),   // sin(201)
    FX32_CONST(-0.37451171875),  // sin(202)
    FX32_CONST(-0.390625),       // sin(203)
    FX32_CONST(-0.40673828125),  // sin(204)
    FX32_CONST(-0.422607421875), // sin(205)
    FX32_CONST(-0.4384765625),   // sin(206)
    FX32_CONST(-0.4541015625),   // sin(207)
    FX32_CONST(-0.469482421875), // sin(208)
    FX32_CONST(-0.48486328125),  // sin(209)
    FX32_CONST(-0.5),            // sin(210)
    FX32_CONST(-0.51513671875),  // sin(211)
    FX32_CONST(-0.530029296875), // sin(212)
    FX32_CONST(-0.544677734375), // sin(213)
    FX32_CONST(-0.55908203125),  // sin(214)
    FX32_CONST(-0.573486328125), // sin(215)
    FX32_CONST(-0.587890625),    // sin(216)
    FX32_CONST(-0.601806640625), // sin(217)
    FX32_CONST(-0.61572265625),  // sin(218)
    FX32_CONST(-0.62939453125),  // sin(219)
    FX32_CONST(-0.642822265625), // sin(220)
    FX32_CONST(-0.656005859375), // sin(221)
    FX32_CONST(-0.669189453125), // sin(222)
    FX32_CONST(-0.681884765625), // sin(223)
    FX32_CONST(-0.694580078125), // sin(224)
    FX32_CONST(-0.70703125),     // sin(225)
    FX32_CONST(-0.71923828125),  // sin(226)
    FX32_CONST(-0.7314453125),   // sin(227)
    FX32_CONST(-0.7431640625),   // sin(228)
    FX32_CONST(-0.754638671875), // sin(229)
    FX32_CONST(-0.76611328125),  // sin(230)
    FX32_CONST(-0.777099609375), // sin(231)
    FX32_CONST(-0.7880859375),   // sin(232)
    FX32_CONST(-0.798583984375), // sin(233)
    FX32_CONST(-0.80908203125),  // sin(234)
    FX32_CONST(-0.819091796875), // sin(235)
    FX32_CONST(-0.8291015625),   // sin(236)
    FX32_CONST(-0.838623046875), // sin(237)
    FX32_CONST(-0.84814453125),  // sin(238)
    FX32_CONST(-0.857177734375), // sin(239)
    FX32_CONST(-0.865966796875), // sin(240)
    FX32_CONST(-0.87451171875),  // sin(241)
    FX32_CONST(-0.883056640625), // sin(242)
    FX32_CONST(-0.89111328125),  // sin(243)
    FX32_CONST(-0.898681640625), // sin(244)
    FX32_CONST(-0.90625),        // sin(245)
    FX32_CONST(-0.91357421875),  // sin(246)
    FX32_CONST(-0.92041015625),  // sin(247)
    FX32_CONST(-0.92724609375),  // sin(248)
    FX32_CONST(-0.93359375),     // sin(249)
    FX32_CONST(-0.939697265625), // sin(250)
    FX32_CONST(-0.945556640625), // sin(251)
    FX32_CONST(-0.951171875),    // sin(252)
    FX32_CONST(-0.956298828125), // sin(253)
    FX32_CONST(-0.961181640625), // sin(254)
    FX32_CONST(-0.9658203125),   // sin(255)
    FX32_CONST(-0.97021484375),  // sin(256)
    FX32_CONST(-0.974365234375), // sin(257)
    FX32_CONST(-0.97802734375),  // sin(258)
    FX32_CONST(-0.981689453125), // sin(259)
    FX32_CONST(-0.98486328125),  // sin(260)
    FX32_CONST(-0.98779296875),  // sin(261)
    FX32_CONST(-0.990234375),    // sin(262)
    FX32_CONST(-0.992431640625), // sin(263)
    FX32_CONST(-0.99462890625),  // sin(264)
    FX32_CONST(-0.99609375),     // sin(265)
    FX32_CONST(-0.99755859375),  // sin(266)
    FX32_CONST(-0.99853515625),  // sin(267)
    FX32_CONST(-0.99951171875),  // sin(268)
    FX32_CONST(-0.999755859375), // sin(269)
    FX32_CONST(-1.0),            // sin(270)
    FX32_CONST(-0.999755859375), // sin(271)
    FX32_CONST(-0.99951171875),  // sin(272)
    FX32_CONST(-0.99853515625),  // sin(273)
    FX32_CONST(-0.99755859375),  // sin(274)
    FX32_CONST(-0.99609375),     // sin(275)
    FX32_CONST(-0.99462890625),  // sin(276)
    FX32_CONST(-0.992431640625), // sin(277)
    FX32_CONST(-0.990234375),    // sin(278)
    FX32_CONST(-0.98779296875),  // sin(279)
    FX32_CONST(-0.98486328125),  // sin(280)
    FX32_CONST(-0.981689453125), // sin(281)
    FX32_CONST(-0.97802734375),  // sin(282)
    FX32_CONST(-0.974365234375), // sin(283)
    FX32_CONST(-0.97021484375),  // sin(284)
    FX32_CONST(-0.9658203125),   // sin(285)
    FX32_CONST(-0.961181640625), // sin(286)
    FX32_CONST(-0.956298828125), // sin(287)
    FX32_CONST(-0.951171875),    // sin(288)
    FX32_CONST(-0.945556640625), // sin(289)
    FX32_CONST(-0.939697265625), // sin(290)
    FX32_CONST(-0.93359375),     // sin(291)
    FX32_CONST(-0.92724609375),  // sin(292)
    FX32_CONST(-0.92041015625),  // sin(293)
    FX32_CONST(-0.91357421875),  // sin(294)
    FX32_CONST(-0.90625),        // sin(295)
    FX32_CONST(-0.898681640625), // sin(296)
    FX32_CONST(-0.89111328125),  // sin(297)
    FX32_CONST(-0.883056640625), // sin(298)
    FX32_CONST(-0.87451171875),  // sin(299)
    FX32_CONST(-0.865966796875), // sin(300)
    FX32_CONST(-0.857177734375), // sin(301)
    FX32_CONST(-0.84814453125),  // sin(302)
    FX32_CONST(-0.838623046875), // sin(303)
    FX32_CONST(-0.8291015625),   // sin(304)
    FX32_CONST(-0.819091796875), // sin(305)
    FX32_CONST(-0.80908203125),  // sin(306)
    FX32_CONST(-0.798583984375), // sin(307)
    FX32_CONST(-0.7880859375),   // sin(308)
    FX32_CONST(-0.777099609375), // sin(309)
    FX32_CONST(-0.76611328125),  // sin(310)
    FX32_CONST(-0.754638671875), // sin(311)
    FX32_CONST(-0.7431640625),   // sin(312)
    FX32_CONST(-0.7314453125),   // sin(313)
    FX32_CONST(-0.71923828125),  // sin(314)
    FX32_CONST(-0.70703125),     // sin(315)
    FX32_CONST(-0.694580078125), // sin(316)
    FX32_CONST(-0.681884765625), // sin(317)
    FX32_CONST(-0.669189453125), // sin(318)
    FX32_CONST(-0.656005859375), // sin(319)
    FX32_CONST(-0.642822265625), // sin(320)
    FX32_CONST(-0.62939453125),  // sin(321)
    FX32_CONST(-0.61572265625),  // sin(322)
    FX32_CONST(-0.601806640625), // sin(323)
    FX32_CONST(-0.587890625),    // sin(324)
    FX32_CONST(-0.573486328125), // sin(325)
    FX32_CONST(-0.55908203125),  // sin(326)
    FX32_CONST(-0.544677734375), // sin(327)
    FX32_CONST(-0.530029296875), // sin(328)
    FX32_CONST(-0.51513671875),  // sin(329)
    FX32_CONST(-0.5),            // sin(330)
    FX32_CONST(-0.48486328125),  // sin(331)
    FX32_CONST(-0.469482421875), // sin(332)
    FX32_CONST(-0.4541015625),   // sin(333)
    FX32_CONST(-0.4384765625),   // sin(334)
    FX32_CONST(-0.422607421875), // sin(335)
    FX32_CONST(-0.40673828125),  // sin(336)
    FX32_CONST(-0.390625),       // sin(337)
    FX32_CONST(-0.37451171875),  // sin(338)
    FX32_CONST(-0.3583984375),   // sin(339)
    FX32_CONST(-0.342041015625), // sin(340)
    FX32_CONST(-0.32568359375),  // sin(341)
    FX32_CONST(-0.30908203125),  // sin(342)
    FX32_CONST(-0.29248046875),  // sin(343)
    FX32_CONST(-0.275634765625), // sin(344)
    FX32_CONST(-0.2587890625),   // sin(345)
    FX32_CONST(-0.241943359375), // sin(346)
    FX32_CONST(-0.224853515625), // sin(347)
    FX32_CONST(-0.2080078125),   // sin(348)
    FX32_CONST(-0.19091796875),  // sin(349)
    FX32_CONST(-0.173583984375), // sin(350)
    FX32_CONST(-0.156494140625), // sin(351)
    FX32_CONST(-0.13916015625),  // sin(352)
    FX32_CONST(-0.121826171875), // sin(353)
    FX32_CONST(-0.1044921875),   // sin(354)
    FX32_CONST(-0.087158203125), // sin(355)
    FX32_CONST(-0.06982421875),  // sin(356)
    FX32_CONST(-0.05224609375),  // sin(357)
    FX32_CONST(-0.034912109375), // sin(358)
    FX32_CONST(-0.017333984375), // sin(359)
    FX32_CONST(0.0),             // sin(360)
    FX32_CONST(0.017333984375),  // sin(361)
    FX32_CONST(0.034912109375),  // sin(362)
    FX32_CONST(0.05224609375),   // sin(363)
    FX32_CONST(0.06982421875),   // sin(364)
    FX32_CONST(0.087158203125),  // sin(365)
    FX32_CONST(0.1044921875),    // sin(366)
    FX32_CONST(0.121826171875),  // sin(367)
    FX32_CONST(0.13916015625),   // sin(368)
    FX32_CONST(0.156494140625),  // sin(369)
    FX32_CONST(0.173583984375),  // sin(370)
    FX32_CONST(0.19091796875),   // sin(371)
    FX32_CONST(0.2080078125),    // sin(372)
    FX32_CONST(0.224853515625),  // sin(373)
    FX32_CONST(0.241943359375),  // sin(374)
    FX32_CONST(0.2587890625),    // sin(375)
    FX32_CONST(0.275634765625),  // sin(376)
    FX32_CONST(0.29248046875),   // sin(377)
    FX32_CONST(0.30908203125),   // sin(378)
    FX32_CONST(0.32568359375),   // sin(379)
    FX32_CONST(0.342041015625),  // sin(380)
    FX32_CONST(0.3583984375),    // sin(381)
    FX32_CONST(0.37451171875),   // sin(382)
    FX32_CONST(0.390625),        // sin(383)
    FX32_CONST(0.40673828125),   // sin(384)
    FX32_CONST(0.422607421875),  // sin(385)
    FX32_CONST(0.4384765625),    // sin(386)
    FX32_CONST(0.4541015625),    // sin(387)
    FX32_CONST(0.469482421875),  // sin(388)
    FX32_CONST(0.48486328125),   // sin(389)
    FX32_CONST(0.5),             // sin(390)
    FX32_CONST(0.51513671875),   // sin(391)
    FX32_CONST(0.530029296875),  // sin(392)
    FX32_CONST(0.544677734375),  // sin(393)
    FX32_CONST(0.55908203125),   // sin(394)
    FX32_CONST(0.573486328125),  // sin(395)
    FX32_CONST(0.587890625),     // sin(396)
    FX32_CONST(0.601806640625),  // sin(397)
    FX32_CONST(0.61572265625),   // sin(398)
    FX32_CONST(0.62939453125),   // sin(399)
    FX32_CONST(0.642822265625),  // sin(400)
    FX32_CONST(0.656005859375),  // sin(401)
    FX32_CONST(0.669189453125),  // sin(402)
    FX32_CONST(0.681884765625),  // sin(403)
    FX32_CONST(0.694580078125),  // sin(404)
    FX32_CONST(0.70703125),      // sin(405)
    FX32_CONST(0.71923828125),   // sin(406)
    FX32_CONST(0.7314453125),    // sin(407)
    FX32_CONST(0.7431640625),    // sin(408)
    FX32_CONST(0.754638671875),  // sin(409)
    FX32_CONST(0.76611328125),   // sin(410)
    FX32_CONST(0.777099609375),  // sin(411)
    FX32_CONST(0.7880859375),    // sin(412)
    FX32_CONST(0.798583984375),  // sin(413)
    FX32_CONST(0.80908203125),   // sin(414)
    FX32_CONST(0.819091796875),  // sin(415)
    FX32_CONST(0.8291015625),    // sin(416)
    FX32_CONST(0.838623046875),  // sin(417)
    FX32_CONST(0.84814453125),   // sin(418)
    FX32_CONST(0.857177734375),  // sin(419)
    FX32_CONST(0.865966796875),  // sin(420)
    FX32_CONST(0.87451171875),   // sin(421)
    FX32_CONST(0.883056640625),  // sin(422)
    FX32_CONST(0.89111328125),   // sin(423)
    FX32_CONST(0.898681640625),  // sin(424)
    FX32_CONST(0.90625),         // sin(425)
    FX32_CONST(0.91357421875),   // sin(426)
    FX32_CONST(0.92041015625),   // sin(427)
    FX32_CONST(0.92724609375),   // sin(428)
    FX32_CONST(0.93359375),      // sin(429)
    FX32_CONST(0.939697265625),  // sin(430)
    FX32_CONST(0.945556640625),  // sin(431)
    FX32_CONST(0.951171875),     // sin(432)
    FX32_CONST(0.956298828125),  // sin(433)
    FX32_CONST(0.961181640625),  // sin(434)
    FX32_CONST(0.9658203125),    // sin(435)
    FX32_CONST(0.97021484375),   // sin(436)
    FX32_CONST(0.974365234375),  // sin(437)
    FX32_CONST(0.97802734375),   // sin(438)
    FX32_CONST(0.981689453125),  // sin(439)
    FX32_CONST(0.98486328125),   // sin(440)
    FX32_CONST(0.98779296875),   // sin(441)
    FX32_CONST(0.990234375),     // sin(442)
    FX32_CONST(0.992431640625),  // sin(443)
    FX32_CONST(0.99462890625),   // sin(444)
    FX32_CONST(0.99609375),      // sin(445)
    FX32_CONST(0.99755859375),   // sin(446)
    FX32_CONST(0.99853515625),   // sin(447)
    FX32_CONST(0.99951171875),   // sin(448)
    FX32_CONST(0.999755859375),  // sin(449)
};

static const u16 UNK_020EDC7E[] = // rotations?
    {
        0x0000, 0x00B7, 0x016D, 0x0223, 0x02D9, 0x038F, 0x0445, 0x04FB, 0x05B1, 0x0667, 0x071D, 0x07D3, 0x0889, 0x093F, 0x09F5, 0x0AAB, 0x0B61, 0x0C17, 0x0CCD, 0x0D83, 0x0E39, 0x0EEF, 0x0FA5, 0x105C, 0x1112, 0x11C8, 0x127E, 0x1334, 0x13EA, 0x14A0, 0x1556, 0x160C, 0x16C2, 0x1778, 0x182E, 0x18E4, 0x199A, 0x1A50, 0x1B06, 0x1BBC, 0x1C72, 0x1D28, 0x1DDE, 0x1E94, 0x1F4A, 0x2000, 0x20B7, 0x216D, 0x2223, 0x22D9, 0x238F, 0x2445, 0x24FB, 0x25B1, 0x2667, 0x271D, 0x27D3, 0x2889, 0x293F, 0x29F5, 0x2AAB, 0x2B61, 0x2C17, 0x2CCD, 0x2D83, 0x2E39, 0x2EEF, 0x2FA5, 0x305C, 0x3112, 0x31C8, 0x327E, 0x3334, 0x33EA, 0x34A0, 0x3556, 0x360C, 0x36C2, 0x3778, 0x382E, 0x38E4, 0x399A, 0x3A50, 0x3B06, 0x3BBC, 0x3C72, 0x3D28, 0x3DDE, 0x3E94, 0x3F4A, 0x4000, 0x40B7, 0x416D, 0x4223, 0x42D9, 0x438F, 0x4445, 0x44FB, 0x45B1, 0x4667, 0x471D, 0x47D3, 0x4889, 0x493F, 0x49F5, 0x4AAB, 0x4B61, 0x4C17, 0x4CCD, 0x4D83, 0x4E39, 0x4EEF, 0x4FA5, 0x505C, 0x5112, 0x51C8, 0x527E, 0x5334, 0x53EA, 0x54A0, 0x5556, 0x560C, 0x56C2, 0x5778, 0x582E, 0x58E4, 0x599A, 0x5A50, 0x5B06, 0x5BBC, 0x5C72, 0x5D28, 0x5DDE, 0x5E94, 0x5F4A, 0x6000, 0x60B7, 0x616D, 0x6223, 0x62D9, 0x638F, 0x6445, 0x64FB, 0x65B1, 0x6667, 0x671D, 0x67D3, 0x6889, 0x693F, 0x69F5, 0x6AAB, 0x6B61, 0x6C17, 0x6CCD, 0x6D83, 0x6E39, 0x6EEF, 0x6FA5, 0x705C, 0x7112, 0x71C8, 0x727E, 0x7334, 0x73EA, 0x74A0, 0x7556, 0x760C, 0x76C2, 0x7778, 0x782E, 0x78E4, 0x799A, 0x7A50, 0x7B06, 0x7BBC, 0x7C72, 0x7D28, 0x7DDE, 0x7E94, 0x7F4A, 0x8000, 0x80B7, 0x816D, 0x8223, 0x82D9, 0x838F, 0x8445, 0x84FB, 0x85B1, 0x8667, 0x871D, 0x87D3, 0x8889, 0x893F, 0x89F5, 0x8AAB, 0x8B61, 0x8C17, 0x8CCD, 0x8D83, 0x8E39, 0x8EEF, 0x8FA5, 0x905C, 0x9112, 0x91C8, 0x927E, 0x9334, 0x93EA, 0x94A0, 0x9556, 0x960C, 0x96C2, 0x9778, 0x982E, 0x98E4, 0x999A, 0x9A50, 0x9B06, 0x9BBC, 0x9C72, 0x9D28, 0x9DDE, 0x9E94, 0x9F4A, 0xA000, 0xA0B7, 0xA16D, 0xA223, 0xA2D9, 0xA38F, 0xA445, 0xA4FB, 0xA5B1, 0xA667, 0xA71D, 0xA7D3, 0xA889, 0xA93F, 0xA9F5, 0xAAAB, 0xAB61, 0xAC17, 0xACCD, 0xAD83, 0xAE39, 0xAEEF, 0xAFA5, 0xB05C, 0xB112, 0xB1C8, 0xB27E, 0xB334, 0xB3EA, 0xB4A0, 0xB556, 0xB60C, 0xB6C2, 0xB778, 0xB82E, 0xB8E4, 0xB99A, 0xBA50, 0xBB06, 0xBBBC, 0xBC72, 0xBD28, 0xBDDE, 0xBE94, 0xBF4A, 0xC000, 0xC0B7, 0xC16D, 0xC223, 0xC2D9, 0xC38F, 0xC445, 0xC4FB, 0xC5B1, 0xC667, 0xC71D, 0xC7D3, 0xC889, 0xC93F, 0xC9F5, 0xCAAB, 0xCB61, 0xCC17, 0xCCCD, 0xCD83, 0xCE39, 0xCEEF, 0xCFA5, 0xD05C, 0xD112, 0xD1C8, 0xD27E, 0xD334, 0xD3EA, 0xD4A0, 0xD556, 0xD60C, 0xD6C2, 0xD778, 0xD82E, 0xD8E4, 0xD99A, 0xDA50, 0xDB06, 0xDBBC, 0xDC72, 0xDD28, 0xDDDE, 0xDE94, 0xDF4A, 0xE000, 0xE0B7, 0xE16D, 0xE223, 0xE2D9, 0xE38F, 0xE445, 0xE4FB, 0xE5B1, 0xE667, 0xE71D, 0xE7D3, 0xE889, 0xE93F, 0xE9F5, 0xEAAB, 0xEB61, 0xEC17, 0xECCD, 0xED83, 0xEE39, 0xEEEF, 0xEFA5, 0xF05C, 0xF112, 0xF1C8, 0xF27E, 0xF334, 0xF3EA, 0xF4A0, 0xF556, 0xF60C, 0xF6C2, 0xF778, 0xF82E, 0xF8E4, 0xF99A, 0xFA50, 0xFB06, 0xFBBC, 0xFC72, 0xFD28, 0xFDDE, 0xFE94, 0xFF4A
    };

static const u16 UNK_020EDB80[] = {
    0x169F, 0x0F14, 0x0B4F, 0x090C, 0x078A, 0x0676, 0x05A7, 0x0506, 0x0486, 0x041C, 0x03C5, 0x037A, 0x033B, 0x0304, 0x02D3, 0x02A9, 0x0283, 0x0261, 0x0243, 0x0227, 0x020E, 0x01F7, 0x01E2, 0x01CF, 0x01BD, 0x01AC, 0x019D, 0x018F, 0x0182, 0x0175, 0x0169, 0x015E, 0x0154, 0x014A, 0x0141, 0x0139, 0x0130, 0x0128, 0x0121, 0x011A, 0x0113, 0x010D, 0x0107, 0x0101, 0x00FB, 0x00F6, 0x00F1, 0x00EC, 0x00E7, 0x00E3, 0x00DE, 0x00DA, 0x00D6, 0x00D2, 0x00CE, 0x00CB, 0x00C7, 0x00C4, 0x00C1, 0x00BD, 0x00BA, 0x00B7, 0x00B4, 0x00B2, 0x00AF, 0x00AC, 0x00AA, 0x00A7, 0x00A5, 0x00A3, 0x00A0, 0x009E, 0x009C, 0x009A, 0x0098, 0x0096, 0x0094, 0x0092, 0x0090, 0x008E, 0x008D, 0x008B, 0x0089, 0x0088, 0x0086, 0x0085, 0x0083, 0x0082, 0x0080, 0x007F, 0x007D, 0x007C, 0x007B, 0x0079, 0x0078, 0x0077, 0x0076, 0x0074, 0x0073, 0x0072, 0x0071, 0x0070, 0x006F, 0x006E, 0x006D, 0x006C, 0x006B, 0x006A, 0x0069, 0x0068, 0x0067, 0x0066, 0x0065, 0x0064, 0x0063, 0x0062, 0x0062, 0x0061, 0x0060, 0x005F, 0x005E, 0x005E, 0x005D, 0x005C, 0x005B, 0x005B, 0x005A
};

/*
 * Temporary prototypes; keep until all files using math_util are decompiled.
 */
s32 Sin(u16 degrees);
s32 Cos(u16 degrees);
s32 Sin_Wrap(u16 degrees);
s32 Cos_Wrap(u16 degrees);
u16 MathUtil_0201B9A0(u16 x);
s32 Sin32(s32 degrees);

u32 GetLCRNGSeed();
void SetLCRNGSeed(u32 seed);
u16 LCRandom(void);

u32 PRandom(u32 seed);

void SetMTRNGSeed(u32 seed);
u32 MTRandom(void);

void MTX22_2DAffine(struct Mtx22 *mtx, u16 radians, fx32 x, fx32 y, u8 type);

s32 CircularDistance(s32 x1, s32 y1, s32 x2, s32 y2);
s32 MathUtil_0201BC84(u16 arg0, s32 arg1);

/*
 * Trigonometric functions
 */
// Returns the sine of a 16-bit unsigned degree value.
s32 Sin(u16 degrees) {
    if (degrees >= 360) {
        return 0;
    } else {
        return gSineTable[degrees];
    }
}
// Returns the cosine of a 16-bit unsigned degree value.
s32 Cos(u16 degrees) {
    if (degrees >= 360) {
        return 0;
    } else {
        return gSineTable[degrees + 90];
    }
}

// Returns the wrapped sine of a 16-bit unsigned degree value.
s32 Sin_Wrap(u16 degrees) {
    return gSineTable[degrees % 360];
}

// Returns the wrapped cosine of a 16-bit unsigned degree value.
s32 Cos_Wrap(u16 degrees) {
    return gSineTable[(degrees % 360) + 90];
}

// Purpose unknown.
u16 MathUtil_0201B9A0(u16 x) {
    return UNK_020EDC7E[x % 360];
}

// Returns the sine of a 32-bit signed degree value.
s32 Sin32(s32 degrees) {
    return gSineTable[(u16)(degrees >> 12) % 360];
}

/*
 * Random number generators
 */
static u32 sMTRNG_State[624]; // Mersenne Twister seed storage/buffer
static u32 sLCRNG_State;

// Returns the Linear-congruential buffer in full.
u32 GetLCRNGSeed() {
    return sLCRNG_State;
}

// Initializes the Linear-congruential buffer with a 32-bit seed.
void SetLCRNGSeed(u32 seed) {
    sLCRNG_State = seed;
}

// Calculates an unsigned 16-bit random integer using the Linear-congruential algorithm.
u16 LCRandom(void) {
    // cycle the RNG
    sLCRNG_State *= 0x41C64E6D;
    sLCRNG_State += 0x6073;
    return (u16)(sLCRNG_State / 65536); // shut up the compiler
}

// Returns a cheap, psuedo-random unsigned 32-bit random integer from a seed.
u32 PRandom(u32 seed) {
    return seed * 1812433253 + 1; // seed from Mersenne Twister algorithm
}

static s32 sMTRNG_Cycles = 625;               // Mersenne Twister cycle counter, 625 default value
static u32 sMTRNG_XOR[2] = { 0, 0x9908b0df }; // Mersenne Twister XOR mask table

// Initializes the Mersenne Twister buffer with a 32-bit seed.
void SetMTRNGSeed(u32 seed) {
    sMTRNG_State[0] = seed;

    for (sMTRNG_Cycles = 1; sMTRNG_Cycles < 624; sMTRNG_Cycles++) {
        sMTRNG_State[sMTRNG_Cycles] = 1812433253 * (sMTRNG_State[sMTRNG_Cycles - 1] ^ (sMTRNG_State[sMTRNG_Cycles - 1] >> 30)) + sMTRNG_Cycles;
    }
}

// Calculates an unsigned 32-bit random integer using the Mersenne Twister algorithm.
u32 MTRandom(void) {
    u32 val;
    s32 i;

    if (sMTRNG_Cycles >= 624) {
        if (sMTRNG_Cycles == 625) {
            SetMTRNGSeed(5489);
        }

        for (i = 0; i < 227; i++) {
            val             = (sMTRNG_State[i] & 0x80000000) | (sMTRNG_State[i + 1] & 0x7fffffff);
            sMTRNG_State[i] = sMTRNG_State[i + 397] ^ (val >> 1) ^ sMTRNG_XOR[val & 0x1];
        }
        for (; i < 623; i++) {
            val             = (sMTRNG_State[i] & 0x80000000) | (sMTRNG_State[i + 1] & 0x7fffffff);
            sMTRNG_State[i] = sMTRNG_State[i + -227] ^ (val >> 1) ^ sMTRNG_XOR[val & 0x1];
        }

        val               = (sMTRNG_State[623] & 0x80000000) | (sMTRNG_State[0] & 0x7fffffff);
        sMTRNG_State[623] = sMTRNG_State[396] ^ (val >> 1) ^ sMTRNG_XOR[val & 0x1];

        sMTRNG_Cycles = 0;
    }

    val = sMTRNG_State[sMTRNG_Cycles++]; // has to be this way in order to match

    val ^= val >> 11;
    val ^= (val << 7) & 0x9d2c5680;
    val ^= (val << 15) & 0xefc60000;
    val ^= val >> 18;

    return val;
}

/*
 * Nitro FX specific functions
 */
// Rotates and scales a 2D plane by a number of degrees.
void MTX22_2DAffine(struct Mtx22 *mtx, u16 radians, fx32 x, fx32 y, u8 type) {
    if (type == 1) {
        radians = (u16)((u32)(radians * 65535) >> 8); // shut up the compiler
    } else if (type == 2) {
        radians = (u16)((u32)(radians * 65535) / 360); // shut up the compiler
    }

    MTX_Rot22_(mtx,
        FX_SinCosTable_[((radians >> 4) * 2)],      // TODO: macros
        FX_SinCosTable_[((radians >> 4) * 2) + 1]); // TODO: macros
    MTX_ScaleApply22(mtx, mtx, x, y);
}

/*
 * Vector functions
 */
// Calculates the circular distance between two vector coordinates.
s32 CircularDistance(s32 x1, s32 y1, s32 x2, s32 y2) {
    struct Vecx32 v1, v2, v3, v4;
    fx32 f1, f2;
    s32 ret;

    // TODO: Code looks like it could have been macroized.
    v1.x = x1 << FX32_INT_SHIFT;
    v1.y = y1 << FX32_INT_SHIFT;
    v1.z = 0;

    v2.x = x2 << FX32_INT_SHIFT;
    v2.y = y2 << FX32_INT_SHIFT;
    v2.z = 0;

    v4.x = 0;
    v4.y = 0;
    v4.z = FX32_MUL(v1.x, v2.y) - FX32_MUL(v2.x, v1.y);

    f1 = v4.x + v4.y + v4.z;

    v1.x = y1 << FX32_INT_SHIFT;
    v1.y = x1 << FX32_INT_SHIFT;
    v1.z = 0;

    VEC_Normalize(&v1, &v3);

    v1.x = x1 << FX32_INT_SHIFT;
    v1.y = y1 << FX32_INT_SHIFT;
    v1.z = 0;

    v2.x = x2 << FX32_INT_SHIFT;
    v2.y = y2 << FX32_INT_SHIFT;
    v2.z = 0;

    VEC_Subtract(&v2, &v1, &v4);
    f2  = VEC_DotProduct(&v3, &v4);
    ret = f2 >> FX32_INT_SHIFT;
    ret = (ret < 0) ? -ret : ret;

    if (f1 <= 0) {
        ret *= -1;
    }
    return ret;
}

s32 MathUtil_0201BC84(u16 arg0, s32 arg1) {
    return (arg1 * 65535) / (FX32_MUL((arg0 * 2) << FX32_INT_SHIFT, FX32_CONST(3.140f)) >> FX32_INT_SHIFT);
}

// Required to protect UNK_020EDB80 from dead-stripping
s32 CALC_SomeDeadstrippedFunction(s32 arg) {
    return UNK_020EDB80[arg];
}
