# 調整手順

* 直進の姿勢制御の中央値を見つける
  * 閾値を変更し、片側だけ制御させ通常直進させる。
  * わざと斜めにした状態で走行を開始
  * ３～４区画ほど走らせ、区画にの中心に収束するように中央値を修正する
  * ↑を左右それぞれ行う
* タイヤ径を確認する
  * 姿勢制御を入れた状態で、5区画(180[mm]*5)程走らせる
* 探索用前壁制御を調整する
  * 正面の壁に対して、2区画と少し離した状態で走行する
* 探索用壁切れを調整する
  * 調整する側の壁を入れて１走行する
* 最短用横壁壁切れを調整する
  * 何ミリ手前で曲がるかを決める
* 最短用前壁壁アリ制御を調整する
  * 壁切れする側の横壁を撤去し、前壁だけでもんだいなくどうさをするかを確認する

* 探索用前壁制御を調整する
  * 