# Multiple-Importance-Sampling-Practice
更改自ray tracing in one weekend 之教學來實作Multiple Importance Sampling
## Brief introduction of Multiple Importance Sampling
由Eric Veach在論文ROBUST MONTE CARLO METHODS FOR LIGHT TRANSPORT SIMULATION 中提出，
之所以要提出MIS是因為在glossy材質的表面上取樣時，單獨使用傳統的sample by light或sample by BRDF
得到的效果都差強人意，於是就兩個方法都使用再根據比例做調整。
