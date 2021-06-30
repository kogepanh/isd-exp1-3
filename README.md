# 演習実験1 テーマ3

## 環境構築

事前に `docker -v` と `docker-compose -v` を確認してください。

ここからは `docker-compose.yml` が存在するディレクトリで実行してください。

```sh
# docker-compose.ymlで定義したserviceのビルドを実行
docker-compose build

# キャッシュのせいで設定変更が反映されない時はオプションをつけるべし
# docker-compose build --no-cache
```

## コンテナ起動

```sh
# コンテナを起動
docker-compose up

# コンテナの中に入る
docker exec -it arm bash
```

## コンパイル

```sh
# コンパイル (*.c → *.mb) or (*.s → *.mb)
make NAME=[FILE_NAME]

# カスファイルを削除
# *.s は削除されないので注意
make clean
```

## コマンド互換表

```sh
# cc-arm -S NAME.c
arm-none-eabi-gcc -S [NAME].c

# as-arm -o NAME.o NAME.s
arm-none-eabi-as -o [NAME].o [NAME].s

# ld-arm -Ttext Ox02000000 -o NAME.out NAME.o
arm-none-eabi-ld -Ttext 0x02000000 -o [NAME].out [NAME].o

# objcopy-arm -O binary NAME.out NAME.bin
arm-none-eabi-objcopy -O binary [NAME].out [NAME].mb

# 逆アセンブル
# das-arm NAME.bin > NAME.txt
arm-none-eabi-objdump -b binary -m arm -D [NAME].mb > [NAME].txt
```

## 終了時

```sh
# コンテナから抜ける
exit

# コンテナを停止
docker-compose down --rmi all
```

## VBA(visualboyadvance)について

この環境でコンパイルした`mb`ファイルは，VBAというエミュレータで実行することができます．

ホストOS上でVBAを実行し，生成した`.mb`ファイルを読み込みます．

VBAの実行形式はホストOSごとに異なります．

+ MacOS
  + 本リポジトリ上の`visualboyadvance-m.app`を使用してください．
+ Windows
  + 本リポジトリ上の`VisualBoyAdvance-1.7.2/VisualBoyAdvance.exe`を使用してください．
+ Linux(Ubuntu)
  + 後述する方法でインストールしてください．

### Ubuntu環境

検証した環境

+ Ubuntu 20.04LTS

GBAのエミュレータとして，本来はVBAの発展版である｢VBA-M｣を利用するようですが，VBA-Mではこの環境でコンパイルした`.mb`ファイルを正常に起動できません．

そのため古い方のVBAが必要ですが，`apt install`ではパッケージが見つかりません．

そこで，debパッケージを直接ダウンロードしてインストールします．

```bash
# 依存関係の解消に必要なライブラリを事前にインストール(人によって異なるかもしれません)
sudo apt-get install libglade2-0
sudo apt-get install libglademm-2.4-1v5

# visualboyadvance(GUI付き)のダウンロード&インストール
wget http://ftp.br.debian.org/debian/pool/main/v/visualboyadvance/visualboyadvance-gtk_1.8.0.dfsg-4_amd64.deb
sudo dpkg -i visualboyadvance-gtk_1.8.0.dfsg-4_amd64.deb

# もしかしたら下記も必要かも
# wget http://ftp.br.debian.org/debian/pool/main/v/visualboyadvance/visualboyadvance_1.8.0.dfsg-4_amd64.deb
# sudo dpkg -i visualboyadvance_1.8.0.dfsg-4_amd64.deb
```

## 実験の課題一覧

JM101のホワイトボードに記載する際に利用してください．

実験1

+ 3.1 ドット表示 (dots2.S)
+ 3.2.1 ドット色変更 (dots3.S)
+ 3.2.2 ドット表示位置変更 (dots4.S)
+ 3.3 C言語化 (dots5.c)

実験2

+ 4.1.2 キー入力(アセンブリ)
+ 4.1.4 キー入力(C言語)

実験3

+ 5.1 画面の塗りつぶし
+ 5.2 点の描画(その1)
+ 5.3 点の描画(その2)
+ 5.4 点の移動x

実験4

+ 5.1 四角形
+ 5.2 円
+ 5.3 線分(その1)
+ 5.4 線分(その2)
