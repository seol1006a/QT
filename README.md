
> 빌드 산출물은 `.gitignore`로 제외되어 있습니다 (`build*/`, `cmake-build-*/`, `moc_*`, `ui_*` 등).

---

## 🛠️ 개발 환경
- **Qt** 6.x (Qt Creator 권장)
- **C++17** 이상
- (선택) **OpenCV 4.x** – 카메라/영상 처리 예제에서 사용
- Windows 10/11, (또는 Linux/WSL)

---

## 🚀 빌드 & 실행 방법

### 방법 1) Qt Creator (가장 쉬움)
1. Qt Creator 실행 → **Open Project**  
2. 원하는 폴더의 `.pro` 또는 `CMakeLists.txt` 선택  
3. Kit 선택 후 **Configure Project** → **Build** → **Run**

### 방법 2) qmake (프로젝트가 .pro를 사용할 때)
```bash
cd AiotClient_tab6
qmake
# Windows (MinGW)
mingw32-make
# 또는 MSVC
nmake
# 실행 파일은 ./build 또는 현재 폴더에 생성
