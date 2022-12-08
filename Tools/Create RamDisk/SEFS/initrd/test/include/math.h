#pragma once

#define LOG10_E 0.4342944819
#define CONST_E 2.718281828459045

#define MIN(_a, _b)						\
({								\
	typeof(_a) __a = (_a);					\
	typeof(_b) __b = (_b);					\
	__a <= __b ? __a : __b;					\
})
#define MAX(_a, _b)						\
({								\
	typeof(_a) __a = (_a);					\
	typeof(_b) __b = (_b);					\
	__a >= __b ? __a : __b;					\
})

// Rounding operations (efficient when n is a power of 2)
// Round down to the nearest multiple of n
#define ROUNDDOWN(a, n)						\
({								\
	uint32_t __a = (uint32_t) (a);				\
	(typeof(a)) (__a - __a % (n));				\
})
// Round up to the nearest multiple of n
#define ROUNDUP(a, n)						\
({								\
	uint32_t __n = (uint32_t) (n);				\
	(typeof(a)) (ROUNDDOWN((uint32_t) (a) + __n - 1, __n));	\
})


uint32_t pow(uint32_t base, uint32_t power);

float sqrt( float x );

float powf( float x, float y );

float log10(float x);

float log(float x);

float logx(float x, float base);

float exp(float x);

static const double powf_log_table[256] = {
											0x1p+0,	-0x0p+0,	// 1, -log2l(1)
											0x1.fcp-1,	0x1.72c7ba20f7327p-7,	// 0.992188, -log2l(0.992188)
											0x1.f80fe03f80fep-1,	0x1.715662c7f3dbcp-6,	// 0.984496, -log2l(0.984496)
											0x1.f42f42f42f42fp-1,	0x1.13eea2b6545dfp-5,	// 0.976923, -log2l(0.976923)
											0x1.f05dcd30dadecp-1,	0x1.6e7f0bd9710ddp-5,	// 0.969466, -log2l(0.969466)
											0x1.ec9b26c9b26cap-1,	0x1.c85f25e12da51p-5,	// 0.962121, -log2l(0.962121)
											0x1.e8e6fa39be8e7p-1,	0x1.10c8cd0c74414p-4,	// 0.954887, -log2l(0.954887)
											0x1.e540f4898d5f8p-1,	0x1.3d0c813e48ep-4,	// 0.947761, -log2l(0.947761)
											0x1.e1a8c536fe1a9p-1,	0x1.68fbf5169e028p-4,	// 0.940741, -log2l(0.940741)
											0x1.de1e1e1e1e1e2p-1,	0x1.949866f0b017bp-4,	// 0.933824, -log2l(0.933824)
											0x1.daa0b3630957dp-1,	0x1.bfe30e28821cp-4,	// 0.927007, -log2l(0.927007)
											0x1.d7303b5cc0ed7p-1,	0x1.eadd1b4ef9a1fp-4,	// 0.92029, -log2l(0.92029)
											0x1.d3cc6e80ebbdbp-1,	0x1.0ac3dc2e0ca0cp-3,	// 0.913669, -log2l(0.913669)
											0x1.d075075075075p-1,	0x1.1ff2046fb7116p-3,	// 0.907143, -log2l(0.907143)
											0x1.cd29c244fe2f3p-1,	0x1.34f99517622aep-3,	// 0.900709, -log2l(0.900709)
											0x1.c9ea5dbf193d5p-1,	0x1.49db19c99a54dp-3,	// 0.894366, -log2l(0.894366)
											0x1.c6b699f5423cep-1,	0x1.5e971b3a4ee8p-3,	// 0.888112, -log2l(0.888112)
											0x1.c38e38e38e38ep-1,	0x1.732e1f41ccdbap-3,	// 0.881944, -log2l(0.881944)
											0x1.c070fe3c070fep-1,	0x1.87a0a8f0ff9b2p-3,	// 0.875862, -log2l(0.875862)
											0x1.bd5eaf57abd5fp-1,	0x1.9bef38a4ffae5p-3,	// 0.869863, -log2l(0.869863)
											0x1.ba5713280dee9p-1,	0x1.b01a4c19f6811p-3,	// 0.863946, -log2l(0.863946)
											0x1.b759f2298375ap-1,	0x1.c4225e7d5e3c6p-3,	// 0.858108, -log2l(0.858108)
											0x1.b4671655e7f24p-1,	0x1.d807e87fa4521p-3,	// 0.852349, -log2l(0.852349)
											0x1.b17e4b17e4b18p-1,	0x1.ebcb6065350a2p-3,	// 0.846667, -log2l(0.846667)
											0x1.ae9f5d3eba7d7p-1,	0x1.ff6d3a16f617fp-3,	// 0.84106, -log2l(0.84106)
											0x1.abca1af286bcap-1,	0x1.0976f3991af9ep-2,	// 0.835526, -log2l(0.835526)
											0x1.a8fe53a8fe53bp-1,	0x1.1326eb8c0aba3p-2,	// 0.830065, -log2l(0.830065)
											0x1.a63bd81a98ef6p-1,	0x1.1cc6bb7e3870fp-2,	// 0.824675, -log2l(0.824675)
											0x1.a3827a3827a38p-1,	0x1.265698fa26c0ap-2,	// 0.819355, -log2l(0.819355)
											0x1.a0d20d20d20d2p-1,	0x1.2fd6b881e82d3p-2,	// 0.814103, -log2l(0.814103)
											0x1.9e2a65187566cp-1,	0x1.39474d95e1649p-2,	// 0.808917, -log2l(0.808917)
											0x1.9b8b577e61371p-1,	0x1.42a88abb54986p-2,	// 0.803797, -log2l(0.803797)
											0x1.98f4bac46d7cp-1,	0x1.4bfaa182b7fe3p-2,	// 0.798742, -log2l(0.798742)
											0x1.9666666666666p-1,	0x1.553dc28dd9724p-2,	// 0.79375, -log2l(0.79375)
											0x1.93e032e1c9f02p-1,	0x1.5e721d95d124dp-2,	// 0.78882, -log2l(0.78882)
											0x1.9161f9add3c0dp-1,	0x1.6797e170c5221p-2,	// 0.783951, -log2l(0.783951)
											0x1.8eeb9533d4065p-1,	0x1.70af3c177f74p-2,	// 0.779141, -log2l(0.779141)
											0x1.8c7ce0c7ce0c8p-1,	0x1.79b85aaad8878p-2,	// 0.77439, -log2l(0.77439)
											0x1.8a15b8a15b8a1p-1,	0x1.82b36978f76d5p-2,	// 0.769697, -log2l(0.769697)
											0x1.87b5f9d4d1bc2p-1,	0x1.8ba09402697edp-2,	// 0.76506, -log2l(0.76506)
											0x1.855d824ca58e9p-1,	0x1.948004ff12dbfp-2,	// 0.760479, -log2l(0.760479)
											0x1.830c30c30c30cp-1,	0x1.9d51e662f92a2p-2,	// 0.755952, -log2l(0.755952)
											0x1.80c1e4bbd595fp-1,	0x1.a6166162e9ec8p-2,	// 0.751479, -log2l(0.751479)
											0x1.7e7e7e7e7e7e8p-1,	0x1.aecd9e78fdbeap-2,	// 0.747059, -log2l(0.747059)
											0x1.7c41df1077c42p-1,	0x1.b777c568f9ae2p-2,	// 0.74269, -log2l(0.74269)
											0x1.7a0be82fa0be8p-1,	0x1.c014fd448fe3ap-2,	// 0.738372, -log2l(0.738372)
											0x1.77dc7c4cf2aeap-1,	0x1.c8a56c6f80bcap-2,	// 0.734104, -log2l(0.734104)
											0x1.75b37e875b37fp-1,	0x1.d12938a39d6fp-2,	// 0.729885, -log2l(0.729885)
											0x1.7390d2a6c405ep-1,	0x1.d9a086f4ad416p-2,	// 0.725714, -log2l(0.725714)
											0x1.71745d1745d17p-1,	0x1.e20b7bd4365a8p-2,	// 0.721591, -log2l(0.721591)
											0x1.6f5e02e4850ffp-1,	0x1.ea6a3b152b1e6p-2,	// 0.717514, -log2l(0.717514)
											0x1.6d4da9b536a6dp-1,	0x1.f2bce7ef7d06bp-2,	// 0.713483, -log2l(0.713483)
											0x1.6b4337c6cb157p-1,	0x1.fb03a50395dbap-2,	// 0.709497, -log2l(0.709497)
											0x1.693e93e93e93fp-1,	0x1.019f4a2edc134p-1,	// 0.705556, -log2l(0.705556)
											0x1.673fa57b0cbabp-1,	0x1.05b6ebbca3d9ap-1,	// 0.701657, -log2l(0.701657)
											0x1.6546546546546p-1,	0x1.09c8c7a1fd74cp-1,	// 0.697802, -log2l(0.697802)
											0x1.63528917c80b3p-1,	0x1.0dd4ee107ae0ap-1,	// 0.693989, -log2l(0.693989)
											0x1.61642c8590b21p-1,	0x1.11db6ef5e7873p-1,	// 0.690217, -log2l(0.690217)
											0x1.5f7b282135f7bp-1,	0x1.15dc59fdc06b7p-1,	// 0.686486, -log2l(0.686486)
											0x1.5d9765d9765d9p-1,	0x1.19d7be92a231p-1,	// 0.682796, -log2l(0.682796)
											0x1.5bb8d015e75bcp-1,	0x1.1dcdabdfad537p-1,	// 0.679144, -log2l(0.679144)
											0x1.59df51b3bea36p-1,	0x1.21be30d1e0ddbp-1,	// 0.675532, -log2l(0.675532)
											0x1.580ad602b580bp-1,	0x1.25a95c196bef3p-1,	// 0.671958, -log2l(0.671958)
											0x1.563b48c20563bp-1,	0x1.298f3c2af6595p-1,	// 0.668421, -log2l(0.668421)
											0x1.5470961d7ca63p-1,	0x1.2d6fdf40e09c5p-1,	// 0.664921, -log2l(0.664921)
											0x1.52aaaaaaaaaabp-1,	0x1.314b535c7b89ep-1,	// 0.661458, -log2l(0.661458)
											0x1.50e97366227cbp-1,	0x1.3521a64737cf3p-1,	// 0.658031, -log2l(0.658031)
											0x1.4f2cddb0d3225p-1,	0x1.38f2e593cda73p-1,	// 0.654639, -log2l(0.654639)
											0x1.4d74d74d74d75p-1,	0x1.3cbf1e9f5cf2fp-1,	// 0.651282, -log2l(0.651282)
											0x1.4bc14e5e0a72fp-1,	0x1.40865e9285f33p-1,	// 0.647959, -log2l(0.647959)
											0x1.4a1231617641p-1,	0x1.4448b2627ade3p-1,	// 0.64467, -log2l(0.64467)
											0x1.48676f31219dcp-1,	0x1.480626d20a876p-1,	// 0.641414, -log2l(0.641414)
											0x1.46c0f6feb6ac6p-1,	0x1.4bbec872a4505p-1,	// 0.638191, -log2l(0.638191)
											0x1.451eb851eb852p-1,	0x1.4f72a3a555958p-1,	// 0.635, -log2l(0.635)
											0x1.4380a3065e3fbp-1,	0x1.5321c49bc0c91p-1,	// 0.631841, -log2l(0.631841)
											0x1.41e6a74981447p-1,	0x1.56cc37590e6c5p-1,	// 0.628713, -log2l(0.628713)
											0x1.4050b59897548p-1,	0x1.5a7207b2d815ap-1,	// 0.625616, -log2l(0.625616)
											0x1.3ebebebebebecp-1,	0x1.5e1341520dbp-1,	// 0.622549, -log2l(0.622549)
											0x1.3d30b3d30b3d3p-1,	0x1.61afefb3d5201p-1,	// 0.619512, -log2l(0.619512)
											0x1.3ba68636adfbp-1,	0x1.65481e2a6477bp-1,	// 0.616505, -log2l(0.616505)
											0x1.3a2027932b48fp-1,	0x1.68dbd7ddd6e15p-1,	// 0.613527, -log2l(0.613527)
											0x1.389d89d89d89ep-1,	0x1.6c6b27ccfc698p-1,	// 0.610577, -log2l(0.610577)
											0x1.371e9f3c04e64p-1,	0x1.6ff618ce24cd7p-1,	// 0.607656, -log2l(0.607656)
											0x1.35a35a35a35a3p-1,	0x1.737cb58fe5716p-1,	// 0.604762, -log2l(0.604762)
											0x1.342bad7f64b39p-1,	0x1.76ff0899daa49p-1,	// 0.601896, -log2l(0.601896)
											0x1.32b78c13521dp-1,	0x1.7a7d1c4d6452p-1,	// 0.599057, -log2l(0.599057)
											0x1.3146e92a10d38p-1,	0x1.7df6fae65e424p-1,	// 0.596244, -log2l(0.596244)
											0x1.2fd9b8396ba9ep-1,	0x1.816cae7bd40b1p-1,	// 0.593458, -log2l(0.593458)
											0x1.2e6fecf2e6fedp-1,	0x1.84de4100b0ce2p-1,	// 0.590698, -log2l(0.590698)
											0x1.2d097b425ed09p-1,	0x1.884bbc446ae3fp-1,	// 0.587963, -log2l(0.587963)
											0x1.2ba6574cae996p-1,	0x1.8bb529f3ab8f3p-1,	// 0.585253, -log2l(0.585253)
											0x1.2a46756e62a46p-1,	0x1.8f1a9398f2d58p-1,	// 0.582569, -log2l(0.582569)
											0x1.28e9ca3a728eap-1,	0x1.927c029d3798ap-1,	// 0.579909, -log2l(0.579909)
											0x1.27904a7904a79p-1,	0x1.95d980488409ap-1,	// 0.577273, -log2l(0.577273)
											0x1.2639eb2639eb2p-1,	0x1.993315c28e8fbp-1,	// 0.574661, -log2l(0.574661)
											0x1.24e6a171024e7p-1,	0x1.9c88cc134f3c3p-1,	// 0.572072, -log2l(0.572072)
											0x1.239662b9f91cbp-1,	0x1.9fdaac2391e1cp-1,	// 0.569507, -log2l(0.569507)
											0x1.2249249249249p-1,	0x1.a328bebd84e8p-1,	// 0.566964, -log2l(0.566964)
											0x1.20fedcba98765p-1,	0x1.a6730c8d44efap-1,	// 0.564444, -log2l(0.564444)
											0x1.1fb78121fb781p-1,	0x1.a9b99e21655ebp-1,	// 0.561947, -log2l(0.561947)
											0x1.1e7307e4ef157p-1,	0x1.acfc7beb75e94p-1,	// 0.559471, -log2l(0.559471)
											0x1.1d31674c59d31p-1,	0x1.b03bae40852ap-1,	// 0.557018, -log2l(0.557018)
											0x1.1bf295cc93903p-1,	0x1.b3773d59a05ffp-1,	// 0.554585, -log2l(0.554585)
											0x1.1ab68a0473c1bp-1,	0x1.b6af315450638p-1,	// 0.552174, -log2l(0.552174)
											0x1.197d3abc65f4fp-1,	0x1.b9e3923313e58p-1,	// 0.549784, -log2l(0.549784)
											0x1.18469ee58469fp-1,	0x1.bd1467ddd70a7p-1,	// 0.547414, -log2l(0.547414)
											0x1.1712ad98b8957p-1,	0x1.c041ba2268731p-1,	// 0.545064, -log2l(0.545064)
											0x1.15e15e15e15e1p-1,	0x1.c36b90b4ebc3ap-1,	// 0.542735, -log2l(0.542735)
											0x1.14b2a7c2fee92p-1,	0x1.c691f33049bap-1,	// 0.540426, -log2l(0.540426)
											0x1.1386822b63cbfp-1,	0x1.c9b4e9169de22p-1,	// 0.538136, -log2l(0.538136)
											0x1.125ce4feeb7a1p-1,	0x1.ccd479d1a1f94p-1,	// 0.535865, -log2l(0.535865)
											0x1.1135c81135c81p-1,	0x1.cff0acb3170e3p-1,	// 0.533613, -log2l(0.533613)
											0x1.10112358e75d3p-1,	0x1.d30988f52c6d3p-1,	// 0.531381, -log2l(0.531381)
											0x1.0eeeeeeeeeeefp-1,	0x1.d61f15bae4663p-1,	// 0.529167, -log2l(0.529167)
											0x1.0dcf230dcf231p-1,	0x1.d9315a1076fa2p-1,	// 0.526971, -log2l(0.526971)
											0x1.0cb1b810ecf57p-1,	0x1.dc405cebb27dcp-1,	// 0.524793, -log2l(0.524793)
											0x1.0b96a673e2808p-1,	0x1.df4c252c5a3e1p-1,	// 0.522634, -log2l(0.522634)
											0x1.0a7de6d1d6086p-1,	0x1.e254b99c83339p-1,	// 0.520492, -log2l(0.520492)
											0x1.096771e4d528cp-1,	0x1.e55a20f0eecf9p-1,	// 0.518367, -log2l(0.518367)
											0x1.0853408534085p-1,	0x1.e85c61c963f0dp-1,	// 0.51626, -log2l(0.51626)
											0x1.07414ba8f0741p-1,	0x1.eb5b82b10609bp-1,	// 0.51417, -log2l(0.51417)
											0x1.06318c6318c63p-1,	0x1.ee578a1eaa83fp-1,	// 0.512097, -log2l(0.512097)
											0x1.0523fbe3367d7p-1,	0x1.f1507e752c6c8p-1,	// 0.51004, -log2l(0.51004)
											0x1.04189374bc6a8p-1,	0x1.f4466603be71dp-1,	// 0.508, -log2l(0.508)
											0x1.030f4c7e7859cp-1,	0x1.f73947063b3fdp-1,	// 0.505976, -log2l(0.505976)
											0x1.0208208208208p-1,	0x1.fa2927a574422p-1,	// 0.503968, -log2l(0.503968)
											0x1.0103091b51f5ep-1,	0x1.fd160df77ed7ap-1,	// 0.501976, -log2l(0.501976)
											0x1p-1,	0x1p+0,	// 0.5, -log2l(0.5)
										};
