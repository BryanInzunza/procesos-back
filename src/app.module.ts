import { Module } from '@nestjs/common';
import { NativeModule } from './native/native.module';

@Module({
  imports: [NativeModule],
})
export class AppModule {}