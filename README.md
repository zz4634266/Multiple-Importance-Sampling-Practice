# Multiple-Importance-Sampling-Practice
更改自ray tracing in one weekend 之教學來實作Multiple Importance Sampling
## Brief introduction of Multiple Importance Sampling
由Eric Veach在論文ROBUST MONTE CARLO METHODS FOR LIGHT TRANSPORT SIMULATION 中提出，  
MIS可減少傳統的複雜計算且融合不同的採樣策略使計算出來的圖瑕疵減少。  
以glossy材質舉例，在表面上取樣時，單獨使用傳統的 sample by light 或 sample by BSDF  
得到的效果都差強人意，於是就兩個方法都使用再根據權重做調整。  
只使用單一方法採樣結果(擷取自Veach的論文):  
![image](https://github.com/zz4634266/Multiple-Importance-Sampling-Practice/blob/main/Veach-example.png?raw=true)
## Result
使用GGX的方法來計算glossy材質的PDF(機率分布函數)，再混和兩種採樣方法:  
### 參數設置
* 由上至下的glossy板子係數(0.05,0.1,0.15,0.20)
* 由左至右的光源半徑與亮度(5-8, 10-4, 20-2, 40-1)  
![image](https://github.com/zz4634266/Multiple-Importance-Sampling-Practice/blob/main/mis.png?raw=true)
