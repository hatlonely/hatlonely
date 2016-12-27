# aws s3

## aws s3

``` sh
1. 创建存储桶
aws s3 mb s3://bucket-name
2. 删除存储桶
aws s3 rb s3://bucket-name [--force]
3. 列出存储桶
aws s3 ls [s3://bucket-name/path]
4. 上传到s3
aws s3 cp <src_path> <dst_path> [--recursive]
5. 同步到s3
aws s3 sync <src_path> <dst_path>
```

## gzip

``` sh
1. 压缩
gzip <filename>
2. 解压
gunzip <filename>
```
