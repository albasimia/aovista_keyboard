# Aovista
**アオビスタ** — 左右分割キーボードのファームウェア・設計リポジトリ

天を仰ぐ2つのジョイスティックが特徴の左右対称性と身体性を損なわない入力体験を重視した自作キーボード。

---

## 特徴

- 左右分割（有線 TRRS 接続）
- 片側 39 キー + ジョイスティック 1 個 + エンコーダー 1 個
- MCU: **RP2040 系**
- ファームウェア: **QMK** / **Vial 対応**
- Mod Tap 対応
- OS Detection による **Emacs キー**（Win/Mac のキー差を吸収）
- RGB バックライト（SK6812 MINI-E）
- 左右の磁石連結

---

## レイアウト概要

- 片側 5 行 × 8 列
- `Fn` キーと `Delete` を入れ替え済み
- 左中段の `Ctrl` 位置に **Emacs キー** を配置

### Emacs キーの動作

| コンビネーション | 動作 |
|---|---|
| Emacs + A | 行頭へ |
| Emacs + E | 行末へ |
| Emacs + H | Backspace |
| Emacs + K | カーソル以降を削除 |
| Emacs + B | ← |
| Emacs + F | → |
| Emacs + P | ↑ |
| Emacs + N | ↓ |
| その他 | Windows: Ctrl / Mac: Command |

> `Ctrl+F` などの既存ショートカットは左下の通常 Ctrl キーで解決する。

---

## ファームウェア構成

```
qmk/
├── aovista.h
├── keyboard.json
├── keymaps/
│   └── default/
│       └── keymap.c
└── vial/
    ├── aovista_via_design_minimal_v2.json
    ├── config.h
    └── rules.mk
```

---

## 設計方針（初号機）

- **できるだけ軽くシンプルに**
- 身体性と配列の成立を最優先
- 無線・中央拡張モジュール・複雑な機構は将来の課題
- コア技術スタック: **QMK + RP2040 + TRRS + 磁石連結**

---

## ドキュメント

- [仕様書](docs/spec.md)