import { Module } from '@nestjs/common';
import { NativeController } from './native.controller';
import { NativeService } from './native.service';

@Module({
  controllers: [NativeController],
  providers: [NativeService],
})
export class NativeModule {}