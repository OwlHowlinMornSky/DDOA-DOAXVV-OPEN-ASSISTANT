/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
*
*     Copyright 2023-2024  Tyler Parret True
*
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at
*
*        http://www.apache.org/licenses/LICENSE-2.0
*
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License.
*
* @Authors
*    Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/
#include "ExactMatchRect.h"

#include <iostream>
#include <string>
#include "../CoreDll/MatchTemplate.h"

#include <filesystem>

#include <opencv2/opencv.hpp>

using namespace ohms;

int GetExactMatchRect() {
	//std::filesystem::path assets = "assets";
	//MatchTemplateInfo info;
	//cv::Mat sample;

	//std::string name = "start";
	//info.isFixed = false;
	//info.thershold = 6554;
	//info.rect = cv::Rect(700, 470, 200, 70);
	//sample = cv::imread("F:\\@Works.Over\\@Code\\Note\\DDOA\\DOAXVV流程\\4 挑战赛\\1680940675.png");

	//// 确保为BGR三个通道
	//if (sample.channels() != 3)
	//	cv::cvtColor(sample, sample, cv::ColorConversionCodes::COLOR_BGRA2BGR, 3);
	//// 确保大小满足要求
	//if (sample.size().width != 960 || sample.size().height != 540) {
	//	auto sz = sample.size();
	//	cv::resize(
	//		sample, sample,
	//		cv::Size(960, 540),
	//		0.0, 0.0, cv::InterpolationFlags::INTER_LINEAR
	//	); // 双线性缩放
	//}

	//MatchTemplate temp(info);
	//temp.LoadMat((assets / (name + ".png")).string());
	//bool res = temp.Match(sample);
	//cv::Rect rect = temp.GetLastMatchRect();

	//std::cout << (res ? "匹配成功" : "匹配失败") << std::endl;
	//std::cout << std::format("Rect: {0}, {1}, {2}, {3}.", rect.x, rect.y, rect.width, rect.height) << std::endl;

	return 0;
}
