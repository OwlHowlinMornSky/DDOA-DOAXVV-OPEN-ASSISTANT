#pragma once

class AppWin32 final {
public:
	AppWin32() = default;
	~AppWin32() = default;

public:
	/**
	 * @brief 初始化
	 * @return true则成功
	*/
	bool Init();

	/**
	 * @brief 运行
	 * @param nShowCmd 
	*/
	void Run(int nShowCmd);

	/**
	 * @brief 清理现场
	*/
	void Drop();
};

/**
 * @brief AppWin的唯一实例
*/
extern AppWin32 app;
