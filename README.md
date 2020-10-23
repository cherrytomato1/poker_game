# 프로그래밍 언어 프로젝트(개인 프로젝트) - 볼링 스코어 보드
- 컴퓨터와 포커게임 진행(콘솔 환경)
- 2015.10 ~ 2015.12

## 개발환경
- 학과 내 리눅스 서버
- vim editor
- c/gcc

# 실행화면

 - 카드 받기
 
 <img src="https://github.com/cherrytomato1/poker_game/blob/main/pokerImage/1_discard.png" />

 자신의 카드만 보여짐, 버릴 카드 선택
 
 - 카드 버리기
 
 <img src="https://github.com/cherrytomato1/poker_game/blob/main/pokerImage/2_showCard.png" />
 
 원하는 카드를 버림, 자신 외의 필레이어는 보여진 카드에 의해 족보가 출력됨, 자신은 자신 전체 카드의 족보 출력
 
 - 컴퓨터 배팅
 
 <img src="https://github.com/cherrytomato1/poker_game/blob/main/pokerImage/3_cpubatt.png" />
 
 컴퓨터 플레이어는 자신의 족보의 가치에 비례하는 확률로 콜 및 다이를 선언, 죽은 플레이어는 출력 제외
 
 - 플레이어 배팅
 
 <img src="https://github.com/cherrytomato1/poker_game/blob/main/pokerImage/4_playerBat.png" />
 
 사용자는 콜 및 다이를 매 카드를 받을 때마다 선언할 수 있음
 
 - 결과
 
 <img src="https://github.com/cherrytomato1/poker_game/blob/main/pokerImage/5_result.png" />
 
 포기를 하지 않은 플레이어들의 모든 카드를 공개하고 공개된 플레이어 중 가장 족보가 높은 플레이어가 승리함
