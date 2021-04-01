# techno_highload_http_server
Ржевский Даниил, разработано в рамках курса highload'а в технопарке

# Start server commands
```
  git clone git@github.com:Rzhevskydd/techno_highload_http_server.git
  cd techno_highload_http_server
  docker build -t http_static_server .  
  docker run -p 8081:8081 http_static_server
```

# Benchmark http_static_server (docker build)
```
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient)
Completed 3000 requests
Completed 6000 requests
Completed 9000 requests
Completed 12000 requests
Completed 15000 requests
Completed 18000 requests
Completed 21000 requests
Completed 24000 requests
Completed 27000 requests
Completed 30000 requests
Finished 30000 requests


Server Software:        http_static_server
Server Hostname:        localhost
Server Port:            8081

Document Path:          /httptest/wikipedia_russia.html
Document Length:        954824 bytes

Concurrency Level:      200
Time taken for tests:   15.027 seconds
Complete requests:      30000
Failed requests:        0
Total transferred:      28649010000 bytes
HTML transferred:       28644720000 bytes
Requests per second:    1996.34 [#/sec] (mean)
Time per request:       100.183 [ms] (mean)
Time per request:       0.501 [ms] (mean, across all concurrent requests)
Transfer rate:          1861760.29 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    2   0.7      2      10
Processing:     7   98   6.2     99     141
Waiting:        0    2   2.9      2      52
Total:          7  100   6.2    100     145

Percentage of the requests served within a certain time (ms)
  50%    100
  66%    101
  75%    102
  80%    102
  90%    104
  95%    106
  98%    108
  99%    110
 100%    145 (longest request)
```
