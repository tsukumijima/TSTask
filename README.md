TSTask
================================

このフォークについて
----------
最新版の TSTask を RecTask 相当にするパッチ、

- tstask.patch ( [http://www.axfc.net/u/3516629](http://www.axfc.net/u/3516629) )
- tstask2-rev2.patch ( [http://www.axfc.net/u/3927997](http://www.axfc.net/u/3927997) )

を適用し、スクランブル解除を行えるようにした TSTask です。  
また、RecTask からスクランブル解除関連の設定画面を移植したほか、同様に RecTask.default.ini のスクランブル解除関連の項目を TSTask.default.ini に移植しています。

SPHD ブランチはこれに加えて

- tstask_sphd.patch・tstask_sphd2.patch ( [http://www.axfc.net/u/3927997](http://www.axfc.net/u/3927997) )

も適用し、TSTask-SPHD（スカパー！プレミアムサービス対応の TSTask ）としています。

ビルドしたものは https://github.com/tsukumijima/DTV-Built に置いてあります。

---------

汎用TS処理プログラム実装研究資料
----------
汎用TS処理プログラム実装研究資料(略称 TSTask)は、パーソナルコンピュータ上において、MPEG-2 TS の処理を行うプログラムの実装を研究する目的で頒布される研究資料です。

この資料は MPEG-2 TS を扱うための基本的な機能を実装しています。  
CAS 処理は実装されていないため、暗号化された一般のテレビ放送を扱うことはできません。


ライセンス
----------
GPL v2
