#CNChess

#### 关于CNChess
CNChess是一个中国象棋人机博弈程序，主要探究如何使计算机在棋类博弈中实现对人类棋手走步的正确反应

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



算法 | 说明 
----|------
SearchEngine | 走步选择基类  
NegamaxEngine | 负极大值算法  
AlphabetaEngine | Alpha-Beta剪枝算法  
Alphabeta_HH | 应用历史启发思想的Alpha-Beta剪枝算法 
Alphabeta_TTEngine | 应用置换表的Alpha-Beta剪枝算法
IDAlphabetaEngine | 应用迭代深化的Alpha-Beta剪枝算法 
PVS_Engine | PVS（主要变例）搜索算法 
