import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { NativeService } from './native/native.service';
import { NativeController } from './native/native.controller';

@Module({
  imports: [],
  controllers: [AppController, NativeController],
  providers: [AppService, NativeService],
})
export class AppModule {}
