#### C++ 坦克大战

##### 功能实现

- 初始化坦克信息
- 移动自己和友军的坦克以及敌军
- 画坦克/擦除坦克
- 移动坦克
- 坦克碰撞
- 创建子弹
- 移动子弹
- 子弹碰撞

##### 结构图

![](D:\Repository\ClassOne\TANK_Dem0\Image\Image1.png)

##### 一些实现细节和考量
- 坦克移动

  > 1. 首先判断坦克是否存活，如果没有死亡，?则判断
  >
  > 2. 一开始给坦克初始化坐标和方向，如果没有检测到?按键操作，则坦克按照初始化的方向向前移动
  >
  > 3. 判断如果不是石块、砖块、河流
  >
  > 4. 如果坦克的方向和接收到的方向一致，0 表示向上移动，1表示向右，2表示向下，3表示向左，坦克能不能移动主要判断坦克左右肩和前面的坐标处是否有东西和地图上的坐标相对应，当反方向移动时，主要分为左右和上下移动，左右只需改变方向，上下只需改变坐标，先移动坦克，再擦除，然后重新画出来

- 子弹移动

  > 关于子弹的移动：
  >
  > ​    1. 子弹--- 障碍物
  >
  > ​    2. 子弹---- 坦克
  >
  > ​    3. 子弹----子弹

- 子弹碰撞检测

  >    1.障碍物：如果子弹进入树林，需要隐藏，不显示也不擦除
  >
  >   如果是草地、雪地、河流，当子弹经过三种障碍物?后，擦除子弹的位置，恢复障碍物，实现同步刷新 
  >
  > 2. 坦克：判断是否属于同一阵营，如果不是，则掉血；子弹子飞行过程中可能遇到不同的障碍物，若是石块，则子弹失效；若是砖块，则都消失；将坦克游戏抽象出三个地图，一个全局地图，一个坦克地图，一个子弹地图，当坦克和子弹的任何操作，都会在全局地图中一一对应，那么子弹失效是怎么处理的呢？? 其实，子弹是加入动态数组中的，当子弹无效时，?就会将其删除 erase实现，然后遍历子弹地图，更新子弹
  >
  > 3. 子弹：子弹和子弹碰撞，检测坐标，将子?弹数组中的生效属性设置为false，将地图中生效属性设置为false,然后调用移除失效子弹的函数，擦除就好

- A*寻路

  > 如何通过寻路找到坦克
  >
  > 首先定义寻找目标，也就是坐标，将坦克的起始位置设置为寻路的起始点，然后检测老巢，如果老巢没有死，则将终点坐标设置为老巢坐标，如果是单人模式，则将目标设置为玩家1坦克；如果是双人模式，则将目标设置为玩家1和玩家2坦克，其它则默认追踪玩家1，然后将起始位置和目标位置传入路径搜索函数搜寻路径

- 关卡

  > 如何进入下一关
  >
  > 是这样的，我这里写了一个判断坦克存活的函数，会?有一个变量保存它的值，规定这个值是-1，则会判断游戏失败，调用游戏失败界面；那是怎么判断游戏失败的呢？ 游戏失败有两种情况，第一是老巢被碾压，第二是玩家生命数为0；接着再来说进入下一关，也就是游戏胜利，即根据判断存活的函数，如果返回的值为1，则判定游戏胜利，调用自动进入下一关的函数



##### 开发环境

> Visual Studio 2015



##### 项目截图

- 主界面

  ![](D:\Repository\ClassOne\TANK_Dem0\Image\Image2.png)

- 单人模式

  ![](D:\Repository\ClassOne\TANK_Dem0\Image\Image3.png)

- 双人模式

  ![](D:\Repository\ClassOne\TANK_Dem0\Image\Image4.png)

- 编辑地图（带跑马灯）

  ![](D:\Repository\ClassOne\TANK_Dem0\Image\Image5.png)

