using System.Drawing;
using HelperKernel;

namespace Helper {
	internal sealed class Pattern :
		MatchCore {

		internal struct Info() {
			public bool isFixed;
			public bool isMasked;
			public float threshold;
			public Rectangle rect = new();
			public List<Point> points = [];
		}

		private float m_thershold; // 判定阈值，差异量上限。
		private Dictionary<string, Point> m_specialPoints = []; // 特殊点

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
		}

		public bool TryMatch(IEye eye) {
			return Match(eye, m_thershold);
		}

		public Point? GetSpecialPointInResultRect(string point_name) {
			if (!m_specialPoints.TryGetValue(point_name, out Point result)) {
				return null;
			}
			result.Offset(GetPreviousMatchedRect().Location);
			return result;
		}

		public Point? GetSpecialPointInSearchRect(string point_name) {
			if (!m_specialPoints.TryGetValue(point_name, out Point result)) {
				return null;
			}
			result.Offset(GetSearchRect().Location);
			return result;
		}

	}
}
