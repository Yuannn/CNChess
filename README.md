# CNChess

#### 关于CNChess
CNChess是一个中国象棋人机博弈程序，主要探究如何使计算机在棋类博弈中实现对人类棋手走步的正确反应。

#### 关于程序
程序主要由三个部分组成：走步产生，局面估值，走步选择。对应类表如下   
走步产生：MoveGenerator  
局面估值：Eveluation    
走步选择：
算法 | 说明 
----|------
SearchEngine | 走步选择基类  
NegamaxEngine | 负极大值算法  
AlphabetaEngine | Alpha-Beta剪枝算法  
Alphabeta_HH | 应用历史启发思想的Alpha-Beta剪枝算法 
Alphabeta_TTEngine | 应用置换表的Alpha-Beta剪枝算法
IDAlphabetaEngine | 应用迭代深化的Alpha-Beta剪枝算法 
PVS_Engine | PVS（主要变例）搜索算法   

程序对象执行交互顺序参考文件“序列图.png”


#### 关于测试
各种算法在不同深度下开局走一步所处理节点数/步
算法\深度 | 1 | 2 | 3 | 4 | 5 | 6 
----|-----|-----|-----|-----|-----|-----
Negamax | 45 | 1566 | 67024 | 2415804 |  | 
Alpha-Beta剪枝算法 | 45 | 1139 | 33675 | 212811 | 2298750 |  
Alpha-Beta剪枝算法 +历史启发 | 45 | 146 | 3259 | 13069 | 259631 | 574272 
Alpha-Beta剪枝算法 +置换表 | 45 | 1139 | 22666 | 126933 | 1039290 |  
PVS	 | 47 | 1196 | 24870 | 232804 | 858784 | 5567315 
Alpha-Beta剪枝算法 +迭代深化	 | 45 | 766 | 34143 | 267671 | 2745070 |  

各种算法在不同深度下开局走一步时间消耗/秒
算法\深度 | 1 | 2 | 3 | 4 | 5 | 6 
----|-----|-----|-----|-----|-----|-----
Negamax | 0.031 | 0.031 | 0.203 | 6.297 |  | 
Alpha-Beta剪枝算法 | 0.016 | 0.016 | 0.109 | 0.578 | 6.172 |  
Alpha-Beta剪枝算法 +历史启发 | 0.016 | 0.032 | 0.047 | 0.062 | 0.719 | 2.063 
Alpha-Beta剪枝算法 +置换表 | 0.031 | 0.031 | 0.078 | 0.422 | 3.156 |  
PVS	 | 0.015 | 0.032 | 0.093 | 0.640 | 2.360 | 14.953 
Alpha-Beta剪枝算法 +迭代深化	 | 0.032 | 0.046 | 0.156 | 0.765 | 7.313 |  

测试计算机使用四核Inter Core i5-3210M CPU 1.0GHZ，8GB RAM，windows8.1 OS  
测试结果步数超过七位数，时间超过30秒时，停止测试


#### 关于改进
预计改进方向如下：  
 - 修复在翻转棋盘无效，悔棋功能，退出按钮显示错误上的BUG  
 - 在走步的数据结构上使用bitboard  
 - 搜索算法上添加fail-soft    Alpha-Beta搜索算法，渴望搜索，MTD(f)搜索，单步延伸思想，蒙特卡洛模拟，深度学习神经网络等  
- 继续优化静态估值的准确性  
- 使用国际象棋作为对象  
- 加入残局库与开局库  

#### 关于开源
CNChess目前全部内容由Yuannn完成于2015年10月，于2016年6月2日开源于github。欢迎各位就程序与算法改进提出意见   
本人邮箱是ikari_genn@outlook.com
CNChess由于是作为一个个人兴趣产生的研究性质的项目，并未提供任何有关界面的代码与资源
