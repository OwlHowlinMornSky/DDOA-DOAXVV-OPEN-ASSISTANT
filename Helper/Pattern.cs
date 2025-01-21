/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
* 
*     Copyright 2023-2025  Tyler Parret True
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
using System.Drawing;
using HelperKernel;

namespace Helper {
	internal sealed class Pattern :
		MatchCore {

		internal struct Info() {
			public bool isFixed;
			public bool isMasked;
			public float threshold;
			public Rectangle rect;
			public List<Point> points = [];
		}

		private float m_thershold; // 判定阈值，差异量上限。
		private Dictionary<string, Point> m_specialPoints = []; // 特殊点
		private List<Point> m_points = [];

		public Pattern(string filepathWithoutExtension, Info info) {
			m_isFloatingArea = !info.isFixed;
			m_searchRect = info.rect;
			m_thershold = info.threshold;

			bool res;
			res = LoadPattern(filepathWithoutExtension + ".png");
			if (!res)
				throw new FileLoadException();

			res = !info.isMasked || LoadMask(filepathWithoutExtension + "[M].png");
			if (!res)
				throw new FileLoadException();

			m_points = new(info.points);
		}

		public bool TryMatch(IEye eye) {
			return Match(eye, m_thershold);
		}

		public Point GetSpecialPointInResultRect(int id) {
			Point result = m_points[id];
			result.Offset(GetPreviousMatchedRect().Location);
			return result;
		}

		public Point GetSpecialPointInSearchRect(int id) {
			Point result = m_points[id];
			result.Offset(GetSearchRect().Location);
			return result;
		}

		public Point? GetSpecialPointInResultRectN(string point_name) {
			if (!m_specialPoints.TryGetValue(point_name, out Point result)) {
				return null;
			}
			result.Offset(GetPreviousMatchedRect().Location);
			return result;
		}

		public Point? GetSpecialPointInSearchRectN(string point_name) {
			if (!m_specialPoints.TryGetValue(point_name, out Point result)) {
				return null;
			}
			result.Offset(GetSearchRect().Location);
			return result;
		}

	}
}
