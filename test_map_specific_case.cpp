/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_map_specific_case.cpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 19:47:00 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/01/24 20:01:39 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(void)
{
	static const char *keys[] = {
	"koiok",
	"knhof",
	"gdkha",
	"kobcl",
	"egbce",
	"dpbij",
	"jdhbb",
	"cmojk",
	"dpnog",
	"nifpk",
	"adabf",
	"eeefm",
	"nopfa",
	"ahmpa",
	"gcpda",
	"fbika",
	"ckdcl",
	"igpml",
	"mjklo",
	"kmfgl",
	"fmnep",
	"okage",
	"ajpdl",
	"klckh",
	"ngbhb",
	"pbnfh",
	"ikdgp",
	"dejdk",
	"nedmh",
	"phdbb",
	"kohlg",
	"ilhga",
	"pokce",
	"jficj",
	"dangm",
	"efdhg",
	"ecfln",
	"leick",
	"ibide",
	"nmjfp",
	"cippp",
	"leepl",
	"ldnap",
	"llddn",
	"nmpfp",
	"dclmi",
	"kpajo",
	"pfcee",
	"ophlp",
	"ggkjk",
	"hgggm",
	"fjoag",
	"glfhe",
	"dgjgk",
	"nejfp",
	"ilgcf",
	"aklga",
	"hlkgl",
	"amgfd",
	"likeo",
	"eccoh",
	"cgcij",
	"hiddo",
	"dkjna",
	"ennlc",
	"aglkk",
	"jpmmn",
	"dodgg",
	"mnopa",
	"mdlfa",
	"ljoie",
	"ajkld",
	"ffcbb",
	"pfpdl",
	"fpidp",
	"jpcee",
	"cpnai",
	"cbbmm",
	"ebbhd",
	"cgibj",
	"dgjlj",
	"ieiki",
	"mmikn",
	"amobi",
	"kfkmm",
	"nodfa",
	"migfd",
	"aniih",
	"afeip",
	"bilpj",
	"djpnf",
	"lkeop",
	"elhka",
	"lkodd",
	"fdijm",
	"hkecj",
	"ofdnd",
	"iinmh",
	"nacel",
	"cpfac",
	"koiok",
	"knhof",
	"gdkha",
	"kobcl",
	"egbce",
	"dpbij",
	"jdhbb",
	"cmojk",
	"dpnog",
	"nifpk",
	"adabf",
	"eeefm",
	"nopfa",
	"ahmpa",
	"gcpda",
	"fbika",
	"ckdcl",
	"igpml",
	"mjklo",
	"kmfgl",
	"fmnep",
	"okage",
	"ajpdl",
	"klckh",
	"ngbhb",
	"pbnfh",
	"ikdgp",
	"dejdk",
	"nedmh",
	"phdbb",
	"kohlg",
	"ilhga",
	"pokce",
	"jficj",
	"dangm",
	"efdhg",
	"ecfln",
	"leick",
	"ibide",
	"nmjfp",
	"cippp",
	"leepl",
	"ldnap",
	"llddn",
	"nmpfp",
	"dclmi",
	"kpajo",
	"pfcee",
	"ophlp",
	"ggkjk",
	"hgggm",
	"fjoag",
	"glfhe",
	"dgjgk",
	"nejfp",
	"ilgcf",
	"aklga",
	"hlkgl",
	"amgfd",
	"likeo",
	"eccoh",
	"cgcij",
	"hiddo",
	"dkjna",
	"ennlc",
	"aglkk",
	"jpmmn",
	"dodgg",
	"mnopa",
	"mdlfa",
	"ljoie",
	"ajkld",
	"ffcbb",
	"pfpdl",
	"fpidp",
	"jpcee",
	"cpnai",
	"cbbmm",
	"ebbhd",
	"cgibj",
	"dgjlj",
	"ieiki",
	"mmikn",
	"amobi",
	"kfkmm",
	"nodfa",
	"migfd",
	"aniih",
	"afeip",
	"bilpj",
	"djpnf",
	"lkeop",
	"elhka",
	"lkodd",
	"fdijm",
	"hkecj",
	"ofdnd",
	"iinmh",
	"nacel",
	"cpfac",
	};	


	static const char *deletion[] = {
	"ebbhd",
	"ebbhd",
	"dgjlj",
	"dangm",
	"djpnf",
	"ikdgp",
	"aglkk",
	"hkecj",
	"fpidp",
	"bilpj",
	"ikdgp",
	"ilhga",
	"kpajo",
	"ilgcf",
	"glfhe",
	"amgfd",
	"jpmmn",
	"hlkgl",
	"kpajo",
	"dkjna",
	"ffcbb",
	"nejfp",
	"dgjgk",
	"fdijm",
	"ngbhb",
	"ilhga",
	"ilhga",
	"bilpj",
	"pokce",
	"cgcij",
	"lkodd",
	"dkjna",
	"nmjfp",
	"pfpdl",
	"ggkjk",
	"mmikn",
	"glfhe",
	"gcpda",
	"cbbmm",
	"ikdgp",
	"ilgcf",
	"ilgcf",
	"nifpk",
	"gdkha",
	"hiddo",
	"cgcij",
	"nopfa",
	"phdbb",
	"kmfgl",
	"amgfd",
	"nmpfp",
	"llddn",
	"nopfa",
	"ggkjk",
	"leick",
	"afeip",
	"dgjlj",
	"mnopa",
	"cbbmm",
	"ennlc",
	"ieiki",
	"ajpdl",
	"dejdk",
	"pfpdl",
	"ofdnd",
	"cpnai",
	"cmojk",
	"ophlp",
	"llddn",
	"kfkmm",
	"ikdgp",
	"nacel",
	"lkeop",
	"efdhg",
	"glfhe",
	"dpbij",
	"ggkjk",
	"ennlc",
	"migfd",
	"mnopa",
	"fpidp",
	"kohlg",
	"eeefm",
	"ibide",
	"cgibj",
	"koiok",
	"ikdgp",
	"likeo",
	"fmnep",
	"ilgcf",
	"ngbhb",
	"knhof",
	"ebbhd",
	"kobcl",
	"ikdgp",
	"ikdgp",
	"pokce",
	"jficj",
	"ikdgp",
	"jpcee",
	"mdlfa",
	"glfhe",
	"pfpdl",
	"eccoh",
	"nmjfp",
	"ebbhd",
	"mjklo",
	"afeip",
	"fdijm",
	"egbce",
	"dpnog",
	"mdlfa",
	"efdhg",
	"kmfgl",
	"likeo",
	"jpmmn",
	"ajkld",
	"migfd",
	"ikdgp",
	"lkeop",
	"leepl",
	"gdkha",
	"lkodd",
	"ajkld",
	"dpbij",
	"ajkld",
	"iinmh",
	"leick",
	"dpbij",
	"jpcee",
	"nopfa",
	"fpidp",
	"dejdk",
	"ibide",
	"aniih",
	"kmfgl",
	"ckdcl",
	"dpbij",
	"cmojk",
	"hiddo",
	"nifpk",
	"ckdcl",
	"amobi",
	"ofdnd",
	"aniih",
	"llddn",
	"dkjna",
	"likeo",
	"phdbb",
	"leepl",
	"hgggm",
	"ajpdl",
	"llddn",
	"hkecj",
	"fdijm",
	"ophlp",
	"dodgg",
	"llddn",
	"ibide",
	"ffcbb",
	"kmfgl",
	"hgggm",
	"kpajo",
	"nacel",
	"cippp",
	"jficj",
	"igpml",
	"dpnog",
	"djpnf",
	"cbbmm",
	"ajkld",
	"glfhe",
	"lkodd",
	"nejfp",
	"koiok",
	"dgjlj",
	"iinmh",
	"dkjna",
	"nmjfp",
	"ebbhd",
	"aklga",
	"ldnap",
	"knhof",
	};

	std::vector<std::string>	keys_vec(keys, keys + sizeof(keys) / sizeof(char *));
	std::vector<std::string>	delete_vec(deletion, deletion + sizeof(deletion) / sizeof(char *));

	ft::map<std::string, size_t>	mymap;
	for (size_t i = 0; i < keys_vec.size(); i++)
		mymap[keys_vec[i]] = i;

	for (size_t i = 0; i < delete_vec.size(); i++)
		mymap.erase(delete_vec[i]);
	mymap.erase("knhof");
	for (ft::map<std::string, size_t>::iterator it = mymap.begin(); it != mymap.end(); it++)
		std::cout << "Key: " << it->first << " : Val: " << it->second << std::endl;
	return (0);
}