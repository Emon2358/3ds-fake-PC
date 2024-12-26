# 3DS Binary Game Editor: eureka

## フォルダー構成

- `source/`: ソースコード
- `sdmc/`: 3DS の SD カードと同じ階層構造
- `build/`: ビルドされたバイナリ

## 使用方法

1. 必要なライブラリをインストール
2. `source/` にソースコードを配置
3. 画像ファイルを `sdmc/wallpapers/` に保存
4. 以下のコマンドでビルド
   ```
   make
   ```
5. 実行
   ```
   make run
   ```
