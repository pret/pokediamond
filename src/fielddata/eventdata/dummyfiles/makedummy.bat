@echo off
REM
REM		まだ作成されていないダミーファイルを生成するための仕組み
REM		必要なファイルで存在しないものはダミーファイルをコピーしてとりあえず生成しておく
REM
REM
if "%1" == "" goto error
if not exist zone_%1.evb (
	sed -e "s/DUMMY/%1/" dummyfiles/zone_dummy.evb > zone_%1.evb
	cvs add zone_%1.evb
)
if not exist zone_%1.evc (
	sed -e "s/DUMMY/%1/" dummyfiles/zone_dummy.evc > zone_%1.evc
	cvs add zone_%1.evc
)
if not exist zone_%1.evd (
	sed -e "s/dummy/%1/" dummyfiles/zone_dummy.evd > zone_%1.evd
	cvs add zone_%1.evd
)
if not exist zone_%1.evp (
	sed -e "s/DUMMY/%1/" dummyfiles/zone_dummy.evp > zone_%1.evp
	cvs add zone_%1.evp
)
if not exist zone_%1evc.h (
	sed -e "s/DUMMY/%1/" dummyfiles/zone_dummyevc.h > zone_%1evc.h
	cvs add zone_%1evc.h
)
if not exist zone_%1evd.h (
	sed -e "s/DUMMY/%1/" dummyfiles/zone_dummyevd.h > zone_%1evd.h
	cvs add zone_%1evd.h
)

goto end
:error
echo ERROR!
exit /b
:end
