# Multiple-Importance-Sampling-Practice
更改自ray tracing in one weekend 之教學來實作Multiple Importance Sampling
## Brief introduction of Multiple Importance Sampling
由Eric Veach在論文ROBUST MONTE CARLO METHODS FOR LIGHT TRANSPORT SIMULATION 中提出，  
MIS可減少傳統的複雜計算且融合不同的採樣策略使計算出來的圖瑕疵減少。  
以glossy材質舉例，在表面上取樣時，單獨使用傳統的 sample by light 或 sample by BSDF  
得到的效果都差強人意，於是就兩個方法都使用再根據比例做調整。  
只使用單一方法採樣結果:  
![image](https://github.com/zz4634266/Multiple-Importance-Sampling-Practice/blob/main/Veach-example.png?raw=true)


![image](https://github.com/zz4634266/Multiple-Importance-Sampling-Practice/blob/main/mis.png?raw=true)
